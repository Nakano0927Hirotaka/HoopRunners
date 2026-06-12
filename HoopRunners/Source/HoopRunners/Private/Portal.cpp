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

static constexpr float PortalPlaneOffset = 10.f;
static constexpr float TeleportCooldown = 0.05f;

// ===== Constructor =====

APortal::APortal()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.TickInterval = 0.03f;

    bReplicates = true;
    SetReplicateMovement(true);

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    Capture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture"));
    Capture->SetupAttachment(Root);
    Capture->bCaptureEveryFrame = false;
    Capture->bCaptureOnMovement = false;

    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
    Trigger->SetupAttachment(Root);
    Trigger->SetBoxExtent(FVector(30.f, 100.f, 100.f));

    PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
    PortalMesh->SetupAttachment(Root);
}

// ===== ヘルパー =====

void APortal::SetupTrigger()
{
    Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Trigger->SetCollisionObjectType(ECC_WorldDynamic);
    Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
    Trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    Trigger->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlap);
    Trigger->OnComponentEndOverlap.AddDynamic(this, &APortal::OnEndOverlap);
}

UTextureRenderTarget2D* APortal::CreateRT()
{
    UTextureRenderTarget2D* RT =
        NewObject<UTextureRenderTarget2D>(this, NAME_None, RF_Transient);
    RT->InitAutoFormat(700, 700);
    RT->UpdateResourceImmediate(true);
    return RT;
}

// ===== BeginPlay =====

void APortal::BeginPlay()
{
    Super::BeginPlay();

    SetupTrigger();

    if (GetNetMode() == NM_DedicatedServer)
    {
        return;
    }

    if (PortalBaseMaterial)
    {
        PortalMID = UMaterialInstanceDynamic::Create(
            PortalBaseMaterial, this);
        PortalMesh->SetMaterial(0, PortalMID);
    }

    Capture->PrimitiveRenderMode =
        ESceneCapturePrimitiveRenderMode::PRM_RenderScenePrimitives;
    Capture->HideComponent(PortalMesh);
    Capture->ShowFlags.Atmosphere = false;
    Capture->ShowFlags.Fog = false;
    Capture->ShowFlags.MotionBlur = false;
    Capture->bCaptureEveryFrame = false;
    Capture->bCaptureOnMovement = false;

    // ===== 明るさ設定 =====
    // 自動露出を無効化して固定値にする
    Capture->PostProcessSettings.bOverride_AutoExposureMethod = true;
    Capture->PostProcessSettings.AutoExposureMethod =
        EAutoExposureMethod::AEM_Manual;

    // 露出補正（値を上げると明るくなる）
    Capture->PostProcessSettings.bOverride_AutoExposureBias = true;
    Capture->PostProcessSettings.AutoExposureBias = 2.0f;

    // 固定露出値（明るさの基準、上げると明るくなる）
    Capture->PostProcessSettings.bOverride_CameraISO = true;
    Capture->PostProcessSettings.CameraISO = 800.f;

    Capture->PostProcessSettings.bOverride_CameraShutterSpeed = true;
    Capture->PostProcessSettings.CameraShutterSpeed = 60.f;
}

// ===== Tick =====

void APortal::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority())
    {
        CleanupTimer += DeltaTime;

        if (CleanupTimer >= 2.f)
        {
            CleanupInvalidActors();
            CleanupTimer = 0.f;
        }

        ProcessTeleport();
    }

    if (!IsNetMode(NM_DedicatedServer))
    {
        UpdateCaptureCamera();
    }
}

// ===== CleanupInvalidActors =====

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

// ===== UpdateCaptureCamera =====
void APortal::UpdateCaptureCamera()
{
    if (!CanUpdateCamera()) return;

    if (!PortalMesh->WasRecentlyRendered(0.1f)) return;

    APawn* Pawn = ViewingPlayer->GetPawn();
    if (!Pawn) return;

    float Dist = FVector::Dist(
        Pawn->GetActorLocation(),
        GetActorLocation());

    if (Dist > 2500.f) return;

    CaptureAccum += 0.05f; // TickIntervalと合わせる

    float CaptureInterval = 0.05f; // 近距離

    if (Dist > 1500.f)
    {
        CaptureInterval = 0.2f;  // 遠距離は間引く
    }
    else if (Dist > 800.f)
    {
        CaptureInterval = 0.1f;  // 中距離
    }

    if (CaptureAccum < CaptureInterval)
    {
        return; // まだ描画しない
    }

    CaptureAccum = 0.f;

    SetupClipPlane();

    // リンク先ポータルの前方にカメラを配置
    FVector CamLocation =
        GetActorLocation()
        + GetActorForwardVector() * 10.f;

    // ===== 回転を追加 =====
    // リンク先の正面方向（ForwardVector）をカメラが向く
    FRotator CamRotation =
        GetActorForwardVector().Rotation();
    // ======================

    Capture->SetWorldLocation(CamLocation);
    Capture->SetWorldRotation(CamRotation);

    Capture->CaptureScene();
}

// ===== CanUpdateCamera =====

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

    if (!Capture->TextureTarget)
    {
        return false;
    }

    return true;
}

// ===== SetupClipPlane =====

void APortal::SetupClipPlane()
{
    Capture->bEnableClipPlane = true;
    Capture->ClipPlaneBase = LinkedPortal->GetActorLocation();
    Capture->ClipPlaneNormal = LinkedPortal->GetActorForwardVector();
}

// ===== DrawPortalDebug =====

void APortal::DrawPortalDebug()
{
    FColor DebugColor = bMainPortal ? FColor::Red : FColor::Blue;

    DrawDebugSphere(
        GetWorld(),
        Capture->GetComponentLocation(),
        30.f, 12, DebugColor, false, 0.f);

    DrawDebugLine(
        GetWorld(),
        Capture->GetComponentLocation(),
        Capture->GetComponentLocation() + Capture->GetForwardVector() * 70.f,
        FColor::Green, false, 0.f);
}

// ===== InitializePortal（サーバーのみ）=====

void APortal::InitializePortal()
{
    // Multicast経由で全クライアントにRTセットアップを命令
    Multicast_SetupRT(bMainPortal);
}

// ===== Multicast_SetupRT =====
// サーバーから全クライアントへRTセットアップを命令する
// A->InitializePortal(), B->InitializePortal() の順で呼ばれる

void APortal::Multicast_SetupRT_Implementation(bool bIsPortalA)
{
    // DedicatedServerは描画不要なのでスキップ
    if (GetNetMode() == NM_DedicatedServer) return;

    // 自分のCaptureRTを生成（Captureが書き込む先）
    if (!CaptureRT)
    {
        CaptureRT = CreateRT();
    }

    // CaptureコンポーネントにRTを設定
    // これにより CaptureScene() の結果が CaptureRT に書き込まれる
    if (Capture)
    {
        Capture->TextureTarget = CaptureRT;
    }

    // ViewingPlayerが未設定の場合はローカルPCを取得
    if (!ViewingPlayer)
    {
        ViewingPlayer = GetWorld()->GetFirstPlayerController();
    }

    if (LinkedPortal)
    {
        // 自分のCaptureRTをリンク先のDisplayRTとして渡す
        // リンク先のメッシュに自分の映像を表示させる
        if (!LinkedPortal->DisplayRT && LinkedPortal->PortalMID)
        {
            LinkedPortal->DisplayRT = CaptureRT;
            LinkedPortal->ApplyDisplayRT();
        }

        // リンク先のCaptureRTを自分のDisplayRTとして受け取る
        // 自分のメッシュにリンク先の映像を表示させる
        if (LinkedPortal->CaptureRT)
        {
            DisplayRT = LinkedPortal->CaptureRT;
            ApplyDisplayRT();
        }

        // Captureカメラの初期位置をリンク先ポータル前方に設定
        // UpdateCaptureCameraで毎フレーム更新されるが初期値として設定
        FVector Pos =
            LinkedPortal->GetActorLocation()
            + LinkedPortal->GetActorForwardVector() * 10.f;

        Capture->SetWorldLocation(Pos);
        Capture->SetWorldRotation(LinkedPortal->GetActorRotation());
    }
}

// ===== OnRep_LinkedPortal =====
// クライアントにLinkedPortalが同期された時に呼ばれる
// Multicast_SetupRTより先にLinkedPortalが届いた場合のフォールバック

void APortal::OnRep_LinkedPortal()
{
    // リンク先未設定またはDedicatedServerはスキップ
    if (!LinkedPortal || GetNetMode() == NM_DedicatedServer) return;

    // 両方のCaptureRTが揃っている場合のみ相互適用
    // （Multicast_SetupRTが両方完了した後に届いたケース）
    if (CaptureRT && LinkedPortal->CaptureRT)
    {
        // 自分のCaptureRTをリンク先のDisplayRTとして設定
        LinkedPortal->DisplayRT = CaptureRT;
        LinkedPortal->ApplyDisplayRT();

        // リンク先のCaptureRTを自分のDisplayRTとして設定
        DisplayRT = LinkedPortal->CaptureRT;
        ApplyDisplayRT();
    }
}

// ===== ApplyDisplayRT =====

void APortal::ApplyDisplayRT()
{
    if (!PortalMID || !DisplayRT) return;

    PortalMID->SetTextureParameterValue(
        TEXT("PortalTexture"), DisplayRT);

    UE_LOG(LogTemp, Warning,
        TEXT("%s ApplyDisplayRT OK CaptureRT=%s DisplayRT=%s"),
        *GetName(),
        *GetNameSafe(CaptureRT),
        *GetNameSafe(DisplayRT));
}

// ===== SetViewingPlayer =====

void APortal::SetViewingPlayer(APlayerController* PC)
{
    ViewingPlayer = PC;
}

// ===== GetLifetimeReplicatedProps =====

void APortal::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(APortal, LinkedPortal);
    DOREPLIFETIME(APortal, OwnerPlayer);
}

// ===== ProcessTeleport =====

void APortal::ProcessTeleport()
{
    if (OverlappingActors.Num() == 0)
    {
        return;
    }

    TArray<AActor*> TeleportList;

    for (AActor* Actor : OverlappingActors)
    {
        if (!CanTeleport(Actor))
        {
            continue;
        }

        FVector CurrFront = GetActorFrontPos(Actor);

        if (!LastPos.Contains(Actor))
        {
            LastPos.Add(Actor, CurrFront);
            continue;
        }

        FVector PrevFront = LastPos[Actor];
        float PrevSide = GetSide(PrevFront);
        float CurrSide = GetSide(CurrFront);

        if (PrevSide * CurrSide < 0.f)
        {
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

// ===== GetActorFrontPos =====

FVector APortal::GetActorFrontPos(AActor* Actor) const
{
    if (ACharacter* Char = Cast<ACharacter>(Actor))
    {
        float Radius =
            Char->GetCapsuleComponent()->GetScaledCapsuleRadius();

        return Actor->GetActorLocation()
            + Actor->GetActorForwardVector() * Radius;
    }

    return Actor->GetActorLocation();
}

// ===== GetPlanePos =====

FVector APortal::GetPlanePos() const
{
    return GetActorLocation()
        + GetActorForwardVector() * PortalPlaneOffset;
}

// ===== GetSide =====

float APortal::GetSide(const FVector& Pos) const
{
    return FVector::DotProduct(
        Pos - GetPlanePos(),
        GetActorForwardVector());
}

// ===== IsInsidePortalBounds =====

bool APortal::IsInsidePortalBounds(const FVector& WorldPos) const
{
    FVector Local =
        GetActorTransform().InverseTransformPosition(WorldPos);

    FVector Extent = Trigger->GetScaledBoxExtent();

    return
        FMath::Abs(Local.Y) <= Extent.Y &&
        FMath::Abs(Local.Z) <= Extent.Z;
}

// ===== CanTeleport =====

bool APortal::CanTeleport(AActor* Actor) const
{
    if (!IsValid(Actor)) return false;

    if (RecentlyTeleported.Contains(Actor)) return false;

    if (!LinkedPortal) return false;

    return true;
}

// ===== TeleportActor =====

void APortal::TeleportActor(AActor* Actor)
{
    if (!Actor || !LinkedPortal) return;

    const FTransform This = GetActorTransform();
    const FTransform Target = LinkedPortal->GetActorTransform();

    FTransform Local =
        Actor->GetActorTransform().GetRelativeTransform(This);

    FTransform NewWorld = Local * Target;

    FVector NewLocation = NewWorld.GetLocation();
    NewLocation += LinkedPortal->GetActorForwardVector() * 50.f;

    if (ACharacter* Char = Cast<ACharacter>(Actor))
    {
        Char->TeleportTo(
            NewLocation,
            NewWorld.GetRotation().Rotator());
    }
    else
    {
        Actor->SetActorLocationAndRotation(
            NewLocation,
            NewWorld.GetRotation().Rotator());
    }

    LinkedPortal->OverlappingActors.Add(Actor);
    LinkedPortal->LastPos.FindOrAdd(Actor) =
        LinkedPortal->GetActorFrontPos(Actor);

    if (ACharacter* Char = Cast<ACharacter>(Actor))
    {
        FVector Vel = Char->GetCharacterMovement()->Velocity;
        FVector LocalVel = This.InverseTransformVector(Vel);
        FVector NewVel = Target.TransformVector(LocalVel);
        Char->GetCharacterMovement()->Velocity = NewVel;
    }

    RecentlyTeleported.Add(Actor);

    FTimerHandle Timer;
    GetWorld()->GetTimerManager().SetTimer(
        Timer,
        FTimerDelegate::CreateUObject(
            this, &APortal::ResetTeleport, Actor),
        TeleportCooldown,
        false);
}

// ===== ResetTeleport =====

void APortal::ResetTeleport(AActor* Actor)
{
    RecentlyTeleported.Remove(Actor);

    if (!Actor) return;

    FVector Front = GetActorFrontPos(Actor);
    LastPos.FindOrAdd(Actor) = Front;

    if (LinkedPortal)
    {
        LinkedPortal->LastPos.FindOrAdd(Actor) = Front;
        LinkedPortal->OverlappingActors.Add(Actor);
    }
}

// ===== OnOverlap =====

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
    LastPos.FindOrAdd(OtherActor) = GetActorFrontPos(OtherActor);

    if (ACharacter* Char = Cast<ACharacter>(OtherActor))
    {
        Char->GetCapsuleComponent()
            ->SetCollisionResponseToChannel(
                ECC_WorldStatic, ECR_Ignore);
    }
}

// ===== OnEndOverlap =====

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
                ECC_WorldStatic, ECR_Block);
    }
}