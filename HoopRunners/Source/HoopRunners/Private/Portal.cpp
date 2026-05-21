#include "Portal.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "EngineUtils.h"

// ===== 定数 =====

static constexpr float PortalPlaneOffset = 10.f;
static constexpr float TeleportCooldown = 0.05f;

// ===== Constructor =====

APortal::APortal()
{
    PrimaryActorTick.bCanEverTick = true;

    Root =
        CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    RootComponent = Root;

    Capture =
        CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture"));

    Capture->SetupAttachment(Root);
    Capture->bCaptureEveryFrame = true;
    Capture->bCaptureOnMovement = false;

    Trigger =
        CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

    Trigger->SetupAttachment(Root);

    Trigger->SetBoxExtent(FVector(30.f, 100.f, 100.f));

    PortalMesh =
        CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));

    PortalMesh->SetupAttachment(Root);
}

// ===== BeginPlay =====

void APortal::BeginPlay()
{
    Super::BeginPlay();

    if (PortalBaseMaterial)
    {
        PortalMID =
            UMaterialInstanceDynamic::Create(
                PortalBaseMaterial,
                this
            );

        PortalMesh->SetMaterial(0, PortalMID);
    }

    if (Capture && RenderTarget)
    {
        Capture->TextureTarget = RenderTarget;
    }


    Capture->PrimitiveRenderMode =
        ESceneCapturePrimitiveRenderMode::PRM_RenderScenePrimitives;

    Capture->HideComponent(PortalMesh);

    Capture->HideActorComponents(this);

    Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    Trigger->SetCollisionObjectType(ECC_WorldDynamic);

    Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);

    Trigger->SetCollisionResponseToChannel(
        ECC_Pawn,
        ECR_Overlap
    );

    Trigger->OnComponentBeginOverlap.AddDynamic(
        this,
        &APortal::OnOverlap
    );

    Trigger->OnComponentEndOverlap.AddDynamic(
        this,
        &APortal::OnEndOverlap
    );

    
}

// ===== Tick =====

void APortal::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CleanupInvalidActors();

    UpdateCaptureCamera();

    ProcessTeleport();
}


void APortal::CleanupInvalidActors()
{
    TArray<AActor*> RemoveList;

    for (auto& Pair : LastPos)
    {
        if (!IsValid(Pair.Key))
        {
            RemoveList.Add(Pair.Key);
        }
    }

    for (AActor* Actor : RemoveList)
    {
        LastPos.Remove(Actor);
        OverlappingActors.Remove(Actor);
    }
}


void APortal::UpdateCaptureCamera()
{
    if (!CanUpdateCamera())
    {
        return;
    }

    SetupClipPlane();

    DrawPortalDebug();

    FVector CamLocation =
        LinkedPortal->GetActorLocation()
        + LinkedPortal->GetActorForwardVector() * 10.f;

    FRotator CamRotation =
        LinkedPortal->GetActorRotation();

    Capture->SetWorldLocation(CamLocation);
    Capture->SetWorldRotation(CamRotation);
}

bool APortal::CanUpdateCamera() const
{
    if (!LinkedPortal || !Capture)
    {
        return false;
    }

    if (!ViewingPlayer)
    {
        return false;
    }

    if (!ViewingPlayer->IsLocalController())
    {
        return false;
    }

    return true;
}

void APortal::SetupClipPlane()
{
    Capture->bEnableClipPlane = true;

    Capture->ClipPlaneBase =
        LinkedPortal->GetActorLocation();

    Capture->ClipPlaneNormal =
        LinkedPortal->GetActorForwardVector();
}

void APortal::DrawPortalDebug()
{
    FColor DebugColor =
        bMainPortal ?
        FColor::Red :
        FColor::Blue;

    DrawDebugSphere(
        GetWorld(),
        Capture->GetComponentLocation(),
        30.f,
        12,
        DebugColor,
        false,
        0.f
    );

    DrawDebugLine(
        GetWorld(),
        Capture->GetComponentLocation(),
        Capture->GetComponentLocation()
        + Capture->GetForwardVector() * 70.f,
        FColor::Green,
        false,
        0.f
    );
}


void APortal::ProcessTeleport()
{
    TArray<AActor*> ActorsCopy =
        OverlappingActors.Array();

    TArray<AActor*> TeleportList;

    for (AActor* Actor : ActorsCopy)
    {
        if (!CanTeleport(Actor))
        {
            continue;
        }

        FVector CurrFront =
            GetActorFrontPos(Actor);

        if (!LastPos.Contains(Actor))
        {
            LastPos.Add(Actor, CurrFront);
            continue;
        }

        FVector PrevFront =
            LastPos[Actor];

        float PrevSide =
            GetSide(PrevFront);

        float CurrSide =
            GetSide(CurrFront);

        if (PrevSide * CurrSide < 0.f)
        {
            // ポータル範囲内だけ許可
            if (IsInsidePortalBounds(CurrFront))
            {
                TeleportList.Add(Actor);
            }
        }

        LastPos[Actor] = CurrFront;
    }

    for (AActor* Actor : TeleportList)
    {
        TeleportActor(Actor);
    }
}

FVector APortal::GetActorFrontPos(AActor* Actor) const
{
    if (ACharacter* Char = Cast<ACharacter>(Actor))
    {
        float Radius =
            Char->GetCapsuleComponent()
            ->GetScaledCapsuleRadius();

        return
            Actor->GetActorLocation() +
            Actor->GetActorForwardVector() * Radius;
    }

    return Actor->GetActorLocation();
}

FVector APortal::GetPlanePos() const
{
    return
        GetActorLocation() +
        GetActorForwardVector() * PortalPlaneOffset;
}

float APortal::GetSide(const FVector& Pos) const
{
    return FVector::DotProduct(
        Pos - GetPlanePos(),
        GetActorForwardVector()
    );
}

bool APortal::IsInsidePortalBounds(const FVector& WorldPos) const
{
    FVector Local =
        GetActorTransform()
        .InverseTransformPosition(WorldPos);

    FVector Extent = Trigger->GetScaledBoxExtent();

    // Xは前後方向なので無視
    return
        FMath::Abs(Local.Y) <= Extent.Y &&
        FMath::Abs(Local.Z) <= Extent.Z;
}

bool APortal::CanTeleport(AActor* Actor) const
{
    if (!IsValid(Actor)) return false;

    if (RecentlyTeleported.Contains(Actor))
    {
        return false;
    }

    if (!LinkedPortal)
    {
        return false;
    }

    return true;
}

void APortal::TeleportActor(AActor* Actor)
{
    if (!Actor || !LinkedPortal)
    {
        return;
    }

    const FTransform This =
        GetActorTransform();

    const FTransform Target =
        LinkedPortal->GetActorTransform();

    FTransform Local =
        Actor->GetActorTransform()
        .GetRelativeTransform(This);

    FTransform NewWorld =
        Local * Target;

    FVector NewLocation =
        NewWorld.GetLocation();

    NewLocation +=
        LinkedPortal->GetActorForwardVector() * 50.f;

    Actor->SetActorLocationAndRotation(
        NewLocation,
        NewWorld.GetRotation().Rotator()
    );

    LinkedPortal->OverlappingActors.Add(Actor);

    LinkedPortal->LastPos.FindOrAdd(Actor) =
        LinkedPortal->GetActorFrontPos(Actor);

    if (ACharacter* Char = Cast<ACharacter>(Actor))
    {
        FVector Vel =
            Char->GetCharacterMovement()->Velocity;

        FVector LocalVel =
            This.InverseTransformVector(Vel);

        FVector NewVel =
            Target.TransformVector(LocalVel);

        Char->GetCharacterMovement()->Velocity =
            NewVel;
    }

    RecentlyTeleported.Add(Actor);

    FTimerHandle Timer;

    GetWorld()->GetTimerManager().SetTimer(
        Timer,
        FTimerDelegate::CreateUObject(
            this,
            &APortal::ResetTeleport,
            Actor
        ),
        TeleportCooldown,
        false
    );
}

void APortal::ResetTeleport(AActor* Actor)
{
    RecentlyTeleported.Remove(Actor);

    if (!Actor) return;

    FVector Front =
        GetActorFrontPos(Actor);

    LastPos.FindOrAdd(Actor) = Front;

    if (LinkedPortal)
    {
        LinkedPortal->LastPos.FindOrAdd(Actor) =
            Front;

        LinkedPortal->OverlappingActors.Add(Actor);
    }
}

// ===== Initialize =====
void APortal::InitializePortal()
{
    if (!LinkedPortal || !Capture) return;
    if (RenderTarget)
    {
        Capture->TextureTarget = RenderTarget;
    }

    if (PortalMID && LinkedPortal->RenderTarget)
    {
        PortalMID->SetTextureParameterValue(
            TEXT("PortalTexture"),
            RenderTarget
        );
    }

    FVector Pos =
        LinkedPortal->GetActorLocation()
        + LinkedPortal->GetActorForwardVector() * 20.f;

    FRotator Rot =
        LinkedPortal->GetActorRotation();

    Capture->SetWorldLocation(Pos);

    Capture->SetWorldRotation(Rot);

    Capture->TextureTarget = RenderTarget;
}

void APortal::SetViewingPlayer(APlayerController* PC)
{
    ViewingPlayer = PC;
}

// ===== Overlap =====

void APortal::OnOverlap(
    UPrimitiveComponent*,
    AActor* OtherActor,
    UPrimitiveComponent*,
    int32,
    bool,
    const FHitResult&)
{
    if (!OtherActor) return;

    OverlappingActors.Add(OtherActor);

    LastPos.FindOrAdd(OtherActor) =
        GetActorFrontPos(OtherActor);

    if (ACharacter* Char = Cast<ACharacter>(OtherActor))
    {
        Char->GetCapsuleComponent()
            ->SetCollisionResponseToChannel(
                ECC_WorldStatic,
                ECR_Ignore
            );
    }
}

void APortal::OnEndOverlap(
    UPrimitiveComponent*,
    AActor* OtherActor,
    UPrimitiveComponent*,
    int32)
{
    if (!OtherActor) return;

    OverlappingActors.Remove(OtherActor);

    LastPos.Remove(OtherActor);

    if (ACharacter* Char = Cast<ACharacter>(OtherActor))
    {
        Char->GetCapsuleComponent()
            ->SetCollisionResponseToChannel(
                ECC_WorldStatic,
                ECR_Block
            );
    }
}