// PortalShooter.cpp

#include "PortalShooter.h"
#include "Portal.h"

#include "Engine/World.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"


APortalShooter::APortalShooter()
{
    PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

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

    APawn* OwnerPawn = Cast<APawn>(GetOwner());

    if (!OwnerPawn)
    {
        return;
    }

    APlayerController* PC = Cast<APlayerController>(OwnerPawn->GetController());

    if (!PC)
    {
        return;
    }

    FVector Start;
    FRotator Rotation;

    PC->GetPlayerViewPoint(Start, Rotation);

    FVector Forward = Rotation.Vector();

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

    APawn* OwnerPawn = Cast<APawn>(GetOwner());

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

    FVector End = Start + Forward * 10000.f;

    FHitResult Hit;

    bool bHit = World->LineTraceSingleByChannel( Hit, Start, End, ECC_Visibility, QueryParams);

    if (!bHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("[Portal] NG: 前方にヒットなし"));
        return false;
    }

    UE_LOG(
        LogTemp, Warning,
        TEXT("[Portal] Hit Actor: %s / Normal: %s"),
        *GetNameSafe(Hit.GetActor()),
        *Hit.ImpactNormal.ToString()
    );


    // ========================================================
    // NoPortal
    // ========================================================

    if (Hit.GetActor() && Hit.GetActor()->ActorHasTag(TEXT("NoPortal")))
    {
        UE_LOG(LogTemp, Warning, TEXT("[Portal] NG: NoPortalタグ"));
        return false;
    }


    // ========================================================
    // ヒット位置・法線
    // ========================================================

    FVector HitPoint = Hit.ImpactPoint;

    FVector Normal = Hit.ImpactNormal.GetSafeNormal();


    // ========================================================
    // 背面の壁を確認
    // ========================================================

    FVector CheckPos = HitPoint - Normal * CellSize;

    FHitResult CheckHit;

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("[Portal] Hit=%s / CurrentA=%s / CurrentB=%s / Preview=%s"),
        *GetNameSafe(Hit.GetActor()),
        *GetNameSafe(CurrentPortalA),
        *GetNameSafe(CurrentPortalB),
        *GetNameSafe(CurrentPreviewActor)
    );

    bool bHasWall = World->LineTraceSingleByChannel(
            CheckHit,
            CheckPos + Normal * 10.f,
            CheckPos - Normal * 10.f,
            ECC_Visibility, QueryParams);


    if (!bHasWall)
    {
        // 背面に壁がない
        return false;
    }


    // ========================================================
    // 2ブロック分の厚みチェック
    // ========================================================

    FVector CheckPos2 = HitPoint - Normal * (CellSize * 2.f);

    FHitResult CheckHit2;

    bool bSecondWall =
        World->LineTraceSingleByChannel(
            CheckHit2,
            CheckPos2 + Normal * 10.f,
            CheckPos2 - Normal * 10.f,
            ECC_Visibility, QueryParams);


    if (bSecondWall)
    {
        // 2ブロック目にも壁がある
        return false;
    }


    // ========================================================
    // 回転用Upベクトル
    // ========================================================

    FVector Up = FVector::UpVector;

    if (FMath::Abs(FVector::DotProduct(Normal, Up)) > 0.99f)
    {
        Up = FVector::ForwardVector;
    }


    // ========================================================
    // 表側ポータル
    // ========================================================

    OutFrontLocation = HitPoint + Normal * PortalOffset;

    OutFrontRotation =
        FRotationMatrix::MakeFromXZ( Normal, Up).Rotator();


    // ========================================================
    // 裏側ポータル
    // ========================================================

    FVector BackNormal = CheckHit.ImpactNormal.GetSafeNormal();

    OutBackLocation =
        CheckHit.ImpactPoint - BackNormal * (PortalOffset * 2.f);

    OutBackRotation =
        FRotationMatrix::MakeFromXZ(-BackNormal, Up).Rotator();


    // ========================================================
    // すべてOK
    // ========================================================

    return true;
}


// ============================================================
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
        UE_LOG(LogTemp, Warning, TEXT("Portal cannot be placed"));

        return;
    }


    // ========================================================
    // Owner
    // ========================================================

    APawn* OwnerPawn = Cast<APawn>(GetOwner());

    APlayerController* PC = OwnerPawn ? Cast<APlayerController>(
            OwnerPawn->GetController()) : nullptr;


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

    SpawnParams.Owner = GetOwner();

    SpawnParams.Instigator = OwnerPawn;

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


    // ポータル生成成功後にクールタイムを開始
    const float CurrentTime = GetPortalGameTime(World);
    nextPortalTime = CurrentTime + PortalCooldown;

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("[Cooldown] Started: Now=%.2f, Next=%.2f, Duration=%.2f"),
        CurrentTime,
        nextPortalTime,
        PortalCooldown
    );

    UE_LOG(LogTemp, Warning, TEXT("Portal Created"));
}


// ============================================================
// StartPortalPreview
// 右クリック押下
// ============================================================
void APortalShooter::StartPortalPreview()
{
    if (!GetWorld())
    {
        return;
    }
    // 青いプレビューを生成
    if (!IsValid(ValidPreviewActor) && ValidPreviewClass)
    {
        ValidPreviewActor = GetWorld()->SpawnActor<AActor>(
            ValidPreviewClass,
            FVector::ZeroVector,
            FRotator::ZeroRotator
        );

        if (IsValid(ValidPreviewActor))
        {
            ValidPreviewActor->SetActorHiddenInGame(true);
        }
    }

    // 赤いプレビューを生成
    if (!IsValid(InvalidPreviewActor) && InvalidPreviewClass)
    {
        InvalidPreviewActor = GetWorld()->SpawnActor<AActor>(
            InvalidPreviewClass,
            FVector::ZeroVector,
            FRotator::ZeroRotator
        );

        if (IsValid(InvalidPreviewActor))
        {
            InvalidPreviewActor->SetActorHiddenInGame(true);
        }
    }


    if (IsValid(ValidPreviewActor))
    {
        // 当たり判定を無効化
        ValidPreviewActor->SetActorEnableCollision(false);

        // 見た目だけ表示する
        ValidPreviewActor->SetActorHiddenInGame(true);
    }

    if (IsValid(InvalidPreviewActor))
    {
        // 当たり判定を無効化
        InvalidPreviewActor->SetActorEnableCollision(false);

        // 見た目だけ表示する
        InvalidPreviewActor->SetActorHiddenInGame(true);
    }

    bPreviewing = true;

    UpdatePreviewColor();
}


// ============================================================
// StopPortalPreview
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

    bCanPlacePortal = CanPlacePortal(Start, Forward, FrontLocation, FrontRotation, BackLocation, BackRotation);


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

    FVector End = Start + Forward * 10000.f;

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
    {
        QueryParams.AddIgnoredActor(OwnerPawn);
    }

    if (IsValid(CurrentPortalA))
    {
        QueryParams.AddIgnoredActor(CurrentPortalA);
    }

    if (IsValid(CurrentPortalB))
    {
        QueryParams.AddIgnoredActor(CurrentPortalB);
    }


    if (IsValid(ValidPreviewActor.Get()))
    {
        QueryParams.AddIgnoredActor(ValidPreviewActor.Get());
    }

    if (IsValid(InvalidPreviewActor.Get()))
    {
        QueryParams.AddIgnoredActor(InvalidPreviewActor.Get());
    }


    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(this);

    // プレイヤーを無視
    if (APawn* Pawn = Cast<APawn>(GetOwner()))
    {
        TraceParams.AddIgnoredActor(Pawn);
    }

    // 設置済みポータルを無視
    if (IsValid(CurrentPortalA))
    {
        TraceParams.AddIgnoredActor(CurrentPortalA);
    }

    if (IsValid(CurrentPortalB))
    {
        TraceParams.AddIgnoredActor(CurrentPortalB);
    }

    // プレビューActorを無視
    if (IsValid(ValidPreviewActor.Get()))
    {
        TraceParams.AddIgnoredActor(ValidPreviewActor.Get());
    }

    if (IsValid(InvalidPreviewActor.Get()))
    {
        TraceParams.AddIgnoredActor(InvalidPreviewActor.Get());
    }

    FHitResult Hit;

    const bool bHit = World->LineTraceSingleByChannel(
        Hit, Start, End, ECC_Visibility, TraceParams);

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

    FVector PreviewLocation;
    FRotator PreviewRotation;

    // 設置可能なら、実際の設置位置をそのまま使用する
    if (bCanPlacePortal)
    {
        PreviewLocation = FrontLocation;
        PreviewRotation = FrontRotation;
    }
    else
    {
        // 設置不可の場合は、照準が当たった壁面に赤いプレビューを表示
        FVector Normal = Hit.ImpactNormal.GetSafeNormal();

        PreviewLocation = Hit.ImpactPoint + Normal * PortalOffset;

        FVector Up = FVector::UpVector;

        if (FMath::Abs(FVector::DotProduct(Normal, Up)) > 0.99f)
        {
            Up = FVector::ForwardVector;
        }

        PreviewRotation =
            FRotationMatrix::MakeFromXZ(Normal, Up).Rotator();
    }

    // ========================================================
    // 青 / 赤の切り替え
    // ========================================================

    UpdatePreviewColor();

    // ========================================================
    // プレビューを移動
    // ========================================================

    if (IsValid(CurrentPreviewActor))
    {
        CurrentPreviewActor->SetActorLocationAndRotation(
            PreviewLocation,
            PreviewRotation
        );
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
// クールタイム
// ============================================================
float APortalShooter::GetRemainingCooldown() const
{
    UWorld* World = GetWorld();

    if (!World)
    {
        return 0.0f;
    }

    const float CurrentTime = GetPortalGameTime(World);

    return FMath::Max(0.0f, nextPortalTime - CurrentTime);
}

bool APortalShooter::IsPortalReady() const
{
    return GetRemainingCooldown() <= 0.0f;
}

float APortalShooter::GetCooldownProgress() const
{
    UWorld* World = GetWorld();

    if (!World)
    {
        return 0.0f;
    }

    const float Now = GetPortalGameTime(World);
    const float Remaining =
        FMath::Max(0.0f, nextPortalTime - Now);

    if (PortalCooldown <= 0.0f)
    {
        return 1.0f;
    }

    return FMath::Clamp(
        1.0f - (Remaining / PortalCooldown),
        0.0f,
        1.0f
    );
}

void APortalShooter::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps
) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APortalShooter, nextPortalTime);
}

float APortalShooter::GetPortalGameTime(const UWorld* World)
{
    if (!World)
    {
        return 0.0f;
    }

    const AGameStateBase* GameState = World->GetGameState();

    if (GameState)
    {
        return GameState->GetServerWorldTimeSeconds();
    }

    return World->GetTimeSeconds();
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
    UTextureRenderTarget2D* RT = NewObject<UTextureRenderTarget2D>(this);

    if (!RT)
    {
        return nullptr;
    }

    RT->InitAutoFormat(1024, 1024);

    RT->ClearColor = FLinearColor::Red;

    RT->UpdateResourceImmediate(true);

    return RT;
}