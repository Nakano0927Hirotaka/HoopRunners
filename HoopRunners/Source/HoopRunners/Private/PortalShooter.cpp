// PortalShooter.cpp

#include "PortalShooter.h"

#include "Portal.h"

#include "DrawDebugHelpers.h"

#include "Engine/TextureRenderTarget2D.h"

#include "GameFramework/PlayerController.h"

#include "Kismet/KismetSystemLibrary.h"

APortalShooter::APortalShooter()
{
    PrimaryActorTick.bCanEverTick = false;

    bReplicates = true;

    RootComponent =
        CreateDefaultSubobject<USceneComponent>(
            TEXT("Root"));
}

void APortalShooter::Fire(
    FVector Start,
    FVector Forward)
{
    if (!HasAuthority())
    {
        ServerFire(Start, Forward);
        return;
    }

    FireInternal(Start, Forward);
}

void APortalShooter::ServerFire_Implementation(
    FVector Start,
    FVector Forward)
{
    FireInternal(Start, Forward);

    UE_LOG(LogTemp, Warning,
        TEXT("ServerFire Start=%s Forward=%s"),
        *Start.ToString(),
        *Forward.ToString());
}

void APortalShooter::FireInternal(
    FVector Start,
    FVector Forward)
{
    UWorld* World = GetWorld();

    if (!World || !PortalClass)
    {
        return;
    }

    APawn* OwnerPawn =
        Cast<APawn>(GetOwner());

    APlayerController* PC =
        OwnerPawn
        ? Cast<APlayerController>(
            OwnerPawn->GetController())
        : nullptr;

    FVector End =
        Start + (Forward * 10000.f);

    UE_LOG(LogTemp, Warning,
        TEXT("Trace Start=%s End=%s"),
        *Start.ToString(),
        *End.ToString());

    // ===== Trace =====

    FCollisionQueryParams QueryParams;

    QueryParams.AddIgnoredActor(this);

    if (OwnerPawn)
    {
        QueryParams.AddIgnoredActor(
            OwnerPawn);
    }

    if (CurrentPortalA)
    {
        QueryParams.AddIgnoredActor(
            CurrentPortalA);
    }

    if (CurrentPortalB)
    {
        QueryParams.AddIgnoredActor(
            CurrentPortalB);
    }

    FHitResult Hit;

    bool bHit =
        World->LineTraceSingleByChannel(
            Hit,
            Start,
            End,
            ECC_Visibility,
            QueryParams);

    if (!bHit)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("Trace Miss"));

        return;
    }

    UE_LOG(LogTemp, Warning,
        TEXT("Hit Actor = %s"),
        *GetNameSafe(Hit.GetActor()));

    // ===== NoPortal =====

    if (Hit.GetActor() &&
        Hit.GetActor()->ActorHasTag(TEXT("NoPortal")))
    {
        UKismetSystemLibrary::PrintString(
            this,
            TEXT("NO Portal"));

        return;
    }

    FVector HitPoint =
        Hit.ImpactPoint;

    FVector Normal =
        Hit.ImpactNormal.GetSafeNormal();

    // ===== Back Wall =====

    FVector CheckPos =
        HitPoint - Normal * CellSize;

    FHitResult CheckHit;

    bool bHasWall =
        World->LineTraceSingleByChannel(
            CheckHit,
            CheckPos + Normal * 10.f,
            CheckPos - Normal * 10.f,
            ECC_Visibility,
            QueryParams);

    if (!bHasWall)
    {
        UKismetSystemLibrary::PrintString(
            this,
            TEXT("No Back Wall"));

        return;
    }

    // ===== 2 Block Check =====

    FVector CheckPos2 =
        HitPoint - Normal * (CellSize * 2.f);

    FHitResult CheckHit2;

    bool bSecondWall =
        World->LineTraceSingleByChannel(
            CheckHit2,
            CheckPos2 + Normal * 10.f,
            CheckPos2 - Normal * 10.f,
            ECC_Visibility,
            QueryParams);

    if (bSecondWall)
    {
        UKismetSystemLibrary::PrintString(
            this,
            TEXT("Too Thick (2 blocks)"));

        return;
    }

    // ===== Rotation =====

    FVector Up =
        FVector::UpVector;

    if (FMath::Abs(
        FVector::DotProduct(
            Normal,
            Up)) > 0.99f)
    {
        Up = FVector::ForwardVector;
    }

    // ===== Spawn Transform =====

    FVector FrontLocation =
        HitPoint + Normal * PortalOffset;

    FVector BackLocation =
        CheckHit.ImpactPoint
        - Normal * PortalOffset;

    FRotator FrontRot =
        FRotationMatrix::MakeFromXZ(
            Normal,
            Up).Rotator();

    FRotator BackRot =
        FRotationMatrix::MakeFromXZ(
            -CheckHit.ImpactNormal,
            Up).Rotator();

    // ===== Debug =====

    DrawDebugSphere(
        World,
        FrontLocation,
        20.f,
        12,
        FColor::Green,
        false,
        5.f);

    DrawDebugSphere(
        World,
        BackLocation,
        20.f,
        12,
        FColor::Blue,
        false,
        5.f);

    // ===== Destroy Old =====

    if (IsValid(CurrentPortalA))
    {
        CurrentPortalA->Destroy();
    }

    if (IsValid(CurrentPortalB))
    {
        CurrentPortalB->Destroy();
    }

    // ===== Spawn =====

    FActorSpawnParameters SpawnParams;

    SpawnParams.Owner = GetOwner();

    SpawnParams.Instigator =
        OwnerPawn;

    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    APortal* A =
        World->SpawnActor<APortal>(
            PortalClass,
            FrontLocation,
            FrontRot,
            SpawnParams);

    APortal* B =
        World->SpawnActor<APortal>(
            PortalClass,
            BackLocation,
            BackRot,
            SpawnParams);

    if (!A || !B)
    {
        return;
    }

    // ===== Setup =====

    A->OwnerPlayer = PC;
    B->OwnerPlayer = PC;

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

    if (PC)
    {
        A->SetViewingPlayer(PC);
        B->SetViewingPlayer(PC);
    }

    UE_LOG(LogTemp, Warning,
        TEXT("Portal Spawn Success"));
}

void APortalShooter::UpdatePreview(
    FVector Start,
    FVector Forward)
{
    UWorld* World = GetWorld();

    if (!World)
    {
        return;
    }

    FVector End =
        Start + Forward * 10000.f;

    FHitResult Hit;

    FCollisionQueryParams QueryParams;

    QueryParams.AddIgnoredActor(this);

    APawn* OwnerPawn =
        Cast<APawn>(GetOwner());

    if (OwnerPawn)
    {
        QueryParams.AddIgnoredActor(
            OwnerPawn);
    }

    bool bHit =
        World->LineTraceSingleByChannel(
            Hit,
            Start,
            End,
            ECC_Visibility,
            QueryParams);

    if (!bHit)
    {
        if (CurrentPreviewActor)
        {
            CurrentPreviewActor->Destroy();
            CurrentPreviewActor = nullptr;
        }

        return;
    }

    FVector HitPoint =
        Hit.ImpactPoint;

    FVector Normal =
        Hit.ImpactNormal.GetSafeNormal();

    if (CurrentPreviewActor)
    {
        CurrentPreviewActor->SetActorLocation(
            HitPoint + Normal * 2.f);

        CurrentPreviewActor->SetActorRotation(
            FRotationMatrix::MakeFromX(
                Normal).Rotator());
    }
}