#include "PortalShooter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Portal.h"
#include "DrawDebugHelpers.h"

APortalShooter::APortalShooter()
{
    PrimaryActorTick.bCanEverTick = false;

    bReplicates = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void APortalShooter::Fire(FVector Start, FVector Forward)
{
    UE_LOG(LogTemp, Warning,
        TEXT("Shooter = %s"),
        *GetName());

    if (!HasAuthority())
    {
        ServerFire(Start, Forward);
        return;
    }

    UWorld* World = GetWorld();
    if (!World || !PortalClass) return;

    // ===== 表トレース =====
    FHitResult Hit;
    FVector End = Start + (Forward * 10000.f);

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    // 既存ポータルも無視（重要）
    if (CurrentPortalA) QueryParams.AddIgnoredActor(CurrentPortalA);
    if (CurrentPortalB) QueryParams.AddIgnoredActor(CurrentPortalB);

    bool bHit = World->LineTraceSingleByChannel(
        Hit, Start, End, ECC_Visibility, QueryParams);

    if (!bHit) return;

    // 設置禁止
    if (Hit.GetActor() && Hit.GetActor()->ActorHasTag(TEXT("NoPortal")))
    {
        UKismetSystemLibrary::PrintString(this, TEXT("NO Portal"));
        return;
    }

    FVector HitPoint = Hit.ImpactPoint;
    FVector Normal = Hit.ImpactNormal.GetSafeNormal();

    // ===== 1マスチェック（超重要）=====
    // 1マス先に壁があるか
    FVector CheckPos = HitPoint - Normal * CellSize;

    FHitResult CheckHit;
    bool bHasWall = World->LineTraceSingleByChannel(
        CheckHit,
        CheckPos + Normal * 10.f,
        CheckPos - Normal * 10.f,
        ECC_Visibility,
        QueryParams
    );

    if (!bHasWall)
    {
        UKismetSystemLibrary::PrintString(this, TEXT("No Back Wall"));
        return;
    }

    // ===== 2マス防止 =====
    FVector CheckPos2 = HitPoint - Normal * (CellSize * 2);

    FHitResult CheckHit2;
    bool bSecondWall = World->LineTraceSingleByChannel(
        CheckHit2,
        CheckPos2 + Normal * 10.f,
        CheckPos2 - Normal * 10.f,
        ECC_Visibility,
        QueryParams
    );

    if (bSecondWall)
    {
        UKismetSystemLibrary::PrintString(this, TEXT("Too Thick (2 blocks)"));
        return;
    }

    // ===== 回転安定 =====
    FVector Up = FVector::UpVector;

    if (FMath::Abs(FVector::DotProduct(Normal, Up)) > 0.99f)
    {
        Up = FVector::ForwardVector;
    }

    // ===== 配置 =====
    FVector FrontLocation = HitPoint + Normal * PortalOffset;
    FVector BackLocation = CheckHit.ImpactPoint - Normal * PortalOffset;

    FRotator FrontRot = FRotationMatrix::MakeFromXZ(Normal, Up).Rotator();
    FRotator BackRot = FRotationMatrix::MakeFromXZ(-CheckHit.ImpactNormal, Up).Rotator();

    // ===== デバッグ =====
    DrawDebugLine(World, HitPoint, BackLocation, FColor::Green, false, 5.f, 0, 2.f);
    DrawDebugSphere(World, FrontLocation, 20, 12, FColor::Green, false, 5.f);
    DrawDebugSphere(World, BackLocation, 20, 12, FColor::Red, false, 5.f);

    // ===== 既存削除 =====
    if (IsValid(CurrentPortalA)) CurrentPortalA->Destroy();
    if (IsValid(CurrentPortalB)) CurrentPortalB->Destroy();

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // ===== 生成 =====
    APortal* A = World->SpawnActor<APortal>(
        PortalClass, FrontLocation, FrontRot, SpawnParams);

    APortal* B = World->SpawnActor<APortal>(
        PortalClass, BackLocation, BackRot, SpawnParams);

    APawn* OwnerPawn = Cast<APawn>(GetOwner());

    APlayerController* PC =
        OwnerPawn
        ? Cast<APlayerController>(OwnerPawn->GetController())
        : nullptr;

    if (A && B)
    {
        A->RenderTarget = RT_PortalA;
        B->RenderTarget = RT_PortalB;

        A->bMainPortal = true;
        B->bMainPortal = false;

        A->LinkedPortal = B;
        B->LinkedPortal = A;

        A->InitializePortal();
        B->InitializePortal();

        CurrentPortalA = A;
        CurrentPortalB = B;

        if (PC && PC->IsLocalController())
        {
            A->SetViewingPlayer(PC);
            B->SetViewingPlayer(PC);
        }
    }
}

void APortalShooter::ServerFire_Implementation(
    FVector Start,
    FVector Forward)
{
    Fire(Start, Forward);
    UE_LOG(LogTemp, Warning, TEXT("ServerFire"));
}

void APortalShooter::UpdatePreview(FVector Start, FVector Forward)
{
    UWorld* World = GetWorld();
    if (!World) return;
    FVector End = Start + Forward * 10000.f;
    FHitResult Hit;
    FCollisionQueryParams QueryParams;
    APlayerController* PC = World->GetFirstPlayerController();
    APawn* PlayerPawn = PC ? PC->GetPawn() : nullptr;
    QueryParams.AddIgnoredActor(this);
    if (PlayerPawn) { QueryParams.AddIgnoredActor(PlayerPawn); }
    bool bHit = World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, QueryParams);
    if (!bHit)
    {
        if (CurrentPreviewActor) {
            CurrentPreviewActor->Destroy();
            CurrentPreviewActor = nullptr;
        }
        return;
    }

    FVector HitPoint = Hit.ImpactPoint; FVector Normal = Hit.ImpactNormal.GetSafeNormal();
    bool bCanPlace = true;
    if (Hit.GetActor() && Hit.GetActor()->ActorHasTag(TEXT("NoPortal")))
    {
        bCanPlace = false;
    }
    if (!CurrentPreviewActor || bLastCanPlace != bCanPlace)
    {
        if (CurrentPreviewActor)
        {
            CurrentPreviewActor->Destroy(); CurrentPreviewActor = nullptr;
        }
        TSubclassOf<AActor> SpawnClass = bCanPlace ? ValidPreviewActor : InvalidPreviewActor;
        if (SpawnClass)
        {
            FActorSpawnParameters SpawnParams;

            SpawnParams.Owner = GetOwner();

            SpawnParams.Instigator =
                Cast<APawn>(GetOwner());

            SpawnParams.SpawnCollisionHandlingOverride =
                ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        }
        bLastCanPlace = bCanPlace;
    }
    if (CurrentPreviewActor)
    {
        CurrentPreviewActor->SetActorLocation(HitPoint + Normal * 2.f);
        CurrentPreviewActor->SetActorRotation(FRotationMatrix::MakeFromX(Normal).Rotator());
    }
}