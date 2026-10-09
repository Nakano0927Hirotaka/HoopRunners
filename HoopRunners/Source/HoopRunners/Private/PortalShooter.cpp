// PortalShooter.cpp

#include "PortalShooter.h"
#include "Portal.h"

#include "Engine/World.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"


APortalShooter::APortalShooter()
{
    PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;

    RootComponent =
        CreateDefaultSubobject<USceneComponent>(
            TEXT("Root"));

    CurrentPortalA = nullptr;
    CurrentPortalB = nullptr;

    ValidPreviewActor = nullptr;
    InvalidPreviewActor = nullptr;
    CurrentPreviewActor = nullptr;

    bPreviewing = false;
    bCanPlacePortal = false;
}


// ============================================================
// BeginPlay
// ============================================================

void APortalShooter::BeginPlay()
{
    Super::BeginPlay();

    // プレビュー用の青ポータルを生成
    if (ValidPreviewClass)
    {
        FActorSpawnParameters SpawnParams;

        SpawnParams.SpawnCollisionHandlingOverride =
            ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        ValidPreviewActor =
            GetWorld()->SpawnActor<AActor>(
                ValidPreviewClass,
                FVector::ZeroVector,
                FRotator::ZeroRotator,
                SpawnParams);

        if (ValidPreviewActor)
        {
            ValidPreviewActor->SetActorHiddenInGame(true);
        }
    }

    // プレビュー用の赤ポータルを生成
    if (InvalidPreviewClass)
    {
        FActorSpawnParameters SpawnParams;

        SpawnParams.SpawnCollisionHandlingOverride =
            ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        InvalidPreviewActor =
            GetWorld()->SpawnActor<AActor>(
                InvalidPreviewClass,
                FVector::ZeroVector,
                FRotator::ZeroRotator,
                SpawnParams);

        if (InvalidPreviewActor)
        {
            InvalidPreviewActor->SetActorHiddenInGame(true);
        }
    }
}


// ============================================================
// Tick
// ============================================================

void APortalShooter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bPreviewing)
    {
        return;
    }

    APawn* OwnerPawn =
        Cast<APawn>(GetOwner());

    if (!OwnerPawn)
    {
        return;
    }

    APlayerController* PC =
        Cast<APlayerController>(
            OwnerPawn->GetController());

    if (!PC)
    {
        return;
    }

    FVector Start;
    FRotator Rotation;

    PC->GetPlayerViewPoint(Start, Rotation);

    FVector Forward =
        Rotation.Vector();

    UpdatePreview(Start, Forward);
}


// ============================================================
// Fire
// 左クリックで呼び出す
// ============================================================

void APortalShooter::Fire(
    FVector Start,
    FVector Forward)
{
    // クライアントならサーバーへ送る
    if (!HasAuthority())
    {
        ServerFire(Start, Forward);
        return;
    }

    FireInternal(Start, Forward);
}


// ============================================================
// ServerFire
// ============================================================

void APortalShooter::ServerFire_Implementation(
    FVector Start,
    FVector Forward)
{
    FireInternal(Start, Forward);

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("ServerFire Start=%s Forward=%s"),
        *Start.ToString(),
        *Forward.ToString());
}


// ============================================================
// CanPlacePortal
//
// ポータルを置けるか判定する。
// プレビューと実際の設置の両方から使用する。
// ============================================================

bool APortalShooter::CanPlacePortal(
    FVector Start,
    FVector Forward,
    FVector& OutFrontLocation,
    FRotator& OutFrontRotation,
    FVector& OutBackLocation,
    FRotator& OutBackRotation)
{
    UWorld* World = GetWorld();

    if (!World || !PortalClass)
    {
        return false;
    }

    // 初期化
    OutFrontLocation = FVector::ZeroVector;
    OutFrontRotation = FRotator::ZeroRotator;

    OutBackLocation = FVector::ZeroVector;
    OutBackRotation = FRotator::ZeroRotator;


    // ========================================================
    // Owner
    // ========================================================

    APawn* OwnerPawn =
        Cast<APawn>(GetOwner());


    // ========================================================
    // Trace設定
    // ========================================================

    FCollisionQueryParams QueryParams;

    QueryParams.AddIgnoredActor(this);

    if (OwnerPawn)
    {
        QueryParams.AddIgnoredActor(OwnerPawn);
    }

    if (CurrentPortalA)
    {
        QueryParams.AddIgnoredActor(CurrentPortalA);
    }

    if (CurrentPortalB)
    {
        QueryParams.AddIgnoredActor(CurrentPortalB);
    }


    // ========================================================
    // 前方Trace
    // ========================================================

    FVector End =
        Start + Forward * 10000.f;

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
        return false;
    }


    // ========================================================
    // NoPortal
    // ========================================================

    if (Hit.GetActor() &&
        Hit.GetActor()->ActorHasTag(TEXT("NoPortal")))
    {
        return false;
    }


    // ========================================================
    // ヒット位置・法線
    // ========================================================

    FVector HitPoint =
        Hit.ImpactPoint;

    FVector Normal =
        Hit.ImpactNormal.GetSafeNormal();


    // ========================================================
    // 背面の壁を確認
    // ========================================================

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
        // 背面に壁がない
        return false;
    }


    // ========================================================
    // 2ブロック分の厚みチェック
    // ========================================================

    FVector CheckPos2 =
        HitPoint -
        Normal * (CellSize * 2.f);

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
        // 2ブロック目にも壁がある
        return false;
    }


    // ========================================================
    // 回転用Upベクトル
    // ========================================================

    FVector Up =
        FVector::UpVector;

    if (FMath::Abs(
        FVector::DotProduct(Normal, Up))
        > 0.99f)
    {
        Up =
            FVector::ForwardVector;
    }


    // ========================================================
    // 表側ポータル
    // ========================================================

    OutFrontLocation =
        HitPoint +
        Normal * PortalOffset;

    OutFrontRotation =
        FRotationMatrix::MakeFromXZ(
            Normal,
            Up).Rotator();


    // ========================================================
    // 裏側ポータル
    // ========================================================

    FVector BackNormal =
        CheckHit.ImpactNormal.GetSafeNormal();

    OutBackLocation =
        CheckHit.ImpactPoint -
        BackNormal * (PortalOffset * 2.f);

    OutBackRotation =
        FRotationMatrix::MakeFromXZ(
            -BackNormal,
            Up).Rotator();


    // ========================================================
    // すべてOK
    // ========================================================

    return true;
}


// ============================================================
// FireInternal
//
// 実際にポータルを生成する。
// ============================================================

void APortalShooter::FireInternal(
    FVector Start, FVector Forward)
{
    UWorld* World = GetWorld();

    if (!World || !PortalClass)
    {
        return;
    }


    // ========================================================
    // ポータル設置可能判定
    // ========================================================

    FVector FrontLocation;
    FRotator FrontRotation;

    FVector BackLocation;
    FRotator BackRotation;


    bool bCanPlace =
        CanPlacePortal(
            Start,
            Forward,
            FrontLocation,
            FrontRotation,
            BackLocation,
            BackRotation);


    if (!bCanPlace)
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("Portal cannot be placed"));

        return;
    }


    // ========================================================
    // Owner
    // ========================================================

    APawn* OwnerPawn =
        Cast<APawn>(GetOwner());

    APlayerController* PC =
        OwnerPawn
        ? Cast<APlayerController>(
            OwnerPawn->GetController())
        : nullptr;


    // ========================================================
    // 古いポータルを削除
    // ========================================================

    if (IsValid(CurrentPortalA))
    {
        CurrentPortalA->Destroy();

        CurrentPortalA = nullptr;
    }

    if (IsValid(CurrentPortalB))
    {
        CurrentPortalB->Destroy();

        CurrentPortalB = nullptr;
    }


    // ========================================================
    // Spawn設定
    // ========================================================

    FActorSpawnParameters SpawnParams;

    SpawnParams.Owner =
        GetOwner();

    SpawnParams.Instigator =
        OwnerPawn;

    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


    // ========================================================
    // 表側ポータル生成
    // ========================================================

    APortal* A =
        World->SpawnActor<APortal>(
            PortalClass,
            FrontLocation,
            FrontRotation,
            SpawnParams);


    // ========================================================
    // 裏側ポータル生成
    // ========================================================

    APortal* B =
        World->SpawnActor<APortal>(
            PortalClass,
            BackLocation,
            BackRotation,
            SpawnParams);


    // ========================================================
    // Spawn失敗
    // ========================================================

    if (!A || !B)
    {
        if (A)
        {
            A->Destroy();
        }

        if (B)
        {
            B->Destroy();
        }

        return;
    }


    // ========================================================
    // Portal設定
    // ========================================================

    A->OwnerPlayer = PC;
    B->OwnerPlayer = PC;

    A->bMainPortal = true;
    B->bMainPortal = false;

    A->LinkedPortal = B;
    B->LinkedPortal = A;


    // ========================================================
    // Portal初期化
    // ========================================================

    A->InitializePortal();
    B->InitializePortal();


    // ========================================================
    // 表示プレイヤー設定
    // ========================================================

    if (PC)
    {
        A->SetViewingPlayer(PC);
        B->SetViewingPlayer(PC);
    }


    // ========================================================
    // 現在のポータルを保存
    // ========================================================

    CurrentPortalA = A;
    CurrentPortalB = B;


    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Portal Created"));
}


// ============================================================
// StartPortalPreview
//
// 右クリック押下
// ============================================================

void APortalShooter::StartPortalPreview()
{
    bPreviewing = true;

    UpdatePreviewColor();
}


// ============================================================
// StopPortalPreview
//
// 右クリックを離した
// ============================================================

void APortalShooter::StopPortalPreview()
{
    bPreviewing = false;

    bCanPlacePortal = false;


    // 青を非表示
    if (ValidPreviewActor)
    {
        ValidPreviewActor->SetActorHiddenInGame(true);
    }


    // 赤を非表示
    if (InvalidPreviewActor)
    {
        InvalidPreviewActor->SetActorHiddenInGame(true);
    }


    CurrentPreviewActor = nullptr;
}


// ============================================================
// UpdatePreview
//
// 右クリック中に毎フレーム呼ばれる
// ============================================================

void APortalShooter::UpdatePreview(
    FVector Start,
    FVector Forward)
{
    if (!bPreviewing)
    {
        return;
    }


    // ========================================================
    // 設置可能判定
    // ========================================================

    FVector FrontLocation;
    FRotator FrontRotation;

    FVector BackLocation;
    FRotator BackRotation;


    bCanPlacePortal =
        CanPlacePortal(
            Start,
            Forward,
            FrontLocation,
            FrontRotation,
            BackLocation,
            BackRotation);


    // ========================================================
    // まず通常のTraceを行う
    //
    // 設置不可でも赤いプレビューを表示するため
    // ========================================================

    UWorld* World = GetWorld();

    if (!World)
    {
        return;
    }


    FVector End =
        Start + Forward * 10000.f;


    FCollisionQueryParams QueryParams;

    QueryParams.AddIgnoredActor(this);


    APawn* OwnerPawn =
        Cast<APawn>(GetOwner());

    if (OwnerPawn)
    {
        QueryParams.AddIgnoredActor(OwnerPawn);
    }

    if (CurrentPortalA)
    {
        QueryParams.AddIgnoredActor(CurrentPortalA);
    }

    if (CurrentPortalB)
    {
        QueryParams.AddIgnoredActor(CurrentPortalB);
    }


    FHitResult Hit;

    bool bHit =
        World->LineTraceSingleByChannel(
            Hit,
            Start,
            End,
            ECC_Visibility,
            QueryParams);


    // ========================================================
    // 何も当たらない
    // ========================================================

    if (!bHit)
    {
        if (ValidPreviewActor)
        {
            ValidPreviewActor->SetActorHiddenInGame(true);
        }

        if (InvalidPreviewActor)
        {
            InvalidPreviewActor->SetActorHiddenInGame(true);
        }

        CurrentPreviewActor = nullptr;

        return;
    }


    // ========================================================
    // プレビュー位置
    // ========================================================

    FVector PreviewLocation =
        Hit.ImpactPoint +
        Hit.ImpactNormal.GetSafeNormal() * 2.f;


    FVector Normal =
        Hit.ImpactNormal.GetSafeNormal();


    FVector Up =
        FVector::UpVector;

    if (FMath::Abs(
        FVector::DotProduct(Normal, Up))
        > 0.99f)
    {
        Up =
            FVector::ForwardVector;
    }


    FRotator PreviewRotation =
        FRotationMatrix::MakeFromXZ(
            Normal,
            Up).Rotator();


    // ========================================================
    // 青 / 赤の切り替え
    // ========================================================

    UpdatePreviewColor();


    // ========================================================
    // 現在のプレビューを移動
    // ========================================================

    if (CurrentPreviewActor)
    {
        CurrentPreviewActor->SetActorLocation(
            PreviewLocation);

        CurrentPreviewActor->SetActorRotation(
            PreviewRotation);
    }
}


// ============================================================
// UpdatePreviewColor
// ============================================================

void APortalShooter::UpdatePreviewColor()
{
    if (bCanPlacePortal)
    {
        // 青を表示
        if (ValidPreviewActor)
        {
            ValidPreviewActor->SetActorHiddenInGame(false);
        }

        // 赤を非表示
        if (InvalidPreviewActor)
        {
            InvalidPreviewActor->SetActorHiddenInGame(true);
        }

        CurrentPreviewActor =
            ValidPreviewActor;
    }
    else
    {
        // 青を非表示
        if (ValidPreviewActor)
        {
            ValidPreviewActor->SetActorHiddenInGame(true);
        }

        // 赤を表示
        if (InvalidPreviewActor)
        {
            InvalidPreviewActor->SetActorHiddenInGame(false);
        }

        CurrentPreviewActor =
            InvalidPreviewActor;
    }
}


// ============================================================
// IsPortalPlaceable
// ============================================================

bool APortalShooter::IsPortalPlaceable() const
{
    return bCanPlacePortal;
}


// ============================================================
// CreatePortalRT
// ============================================================

UTextureRenderTarget2D*
APortalShooter::CreatePortalRT()
{
    UTextureRenderTarget2D* RT =
        NewObject<UTextureRenderTarget2D>(this);

    if (!RT)
    {
        return nullptr;
    }

    RT->InitAutoFormat(
        1024,
        1024);

    RT->ClearColor =
        FLinearColor::Red;

    RT->UpdateResourceImmediate(true);

    return RT;
}