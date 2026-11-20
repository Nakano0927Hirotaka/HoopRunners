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
// APortal.cpp：ポータルの映像描画、Overlap管理、プレイヤーテレポートを担当

static constexpr float PortalPlaneOffset = 10.f;
static constexpr float TeleportCooldown = 0.05f;

// ===== Constructor =====

// ============================================================
// 1. コンストラクタ・コンポーネント初期化
// ============================================================

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

// ============================================================
// 2. Trigger・Render Target生成
// ============================================================

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

// ============================================================
// 3. BeginPlay・初期設定
// ============================================================

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
    // Capture->ShowFlags.Atmosphere = false;
    // Capture->ShowFlags.Fog = false;
    // Capture->ShowFlags.MotionBlur = false;
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

// ============================================================
// 4. 毎フレーム更新
// ============================================================

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

// ============================================================
// 5. 無効Actorの整理
// ============================================================

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
// ============================================================
// 6. ポータルカメラ・映像描画
// ============================================================

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
        GetActorLocation() + GetActorForwardVector() * 10.f;

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

// ============================================================
// 7. ポータル描画の初期化・ネットワーク同期
// ============================================================

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


void APortal::SetViewingPlayer(APlayerController* PC)
{
    ViewingPlayer = PC;
}


void APortal::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(APortal, LinkedPortal);
    DOREPLIFETIME(APortal, OwnerPlayer);
}


// ============================================================
// 8. テレポート判定・実行
// ============================================================

void APortal::ProcessTeleport()
{
    if (OverlappingActors.Num() == 0) return;

    TArray<AActor*> TeleportList;

    for (AActor* Actor : OverlappingActors)
    {
        if (!CanTeleport(Actor)) continue;

        FVector CurrPos = Actor->GetActorLocation();

        // カプセルの半径を取得
        float Radius = 42.f;

        if (ACharacter* Char = Cast<ACharacter>(Actor))
        {
            Radius = Char->GetCapsuleComponent()->GetScaledCapsuleRadius();
        }

        // ポータル面からプレイヤー中心までの距離
        float CurrentSide = GetSide(CurrPos);

        // ポータルの開口範囲内か確認
        bool bInsideBounds = IsInsidePortalBounds(CurrPos);

        UE_LOG(
            LogTemp,
            Warning,
            TEXT("Portal Check: Actor=%s Side=%f Radius=%f Inside=%d"),
            *Actor->GetName(),
            CurrentSide,
            Radius,
            bInsideBounds
        );

        // カプセルがポータル面に到達したらワープ
        if (FMath::Abs(CurrentSide) <= Radius + 5.f && bInsideBounds)
        {
            UE_LOG(
                LogTemp,
                Warning,
                TEXT("Portal Teleport Triggered: %s"),
                *Actor->GetName()
            );

            TeleportList.Add(Actor);
        }

        LastPos.FindOrAdd(Actor) = CurrPos;
    }

    // テレポート実行
    for (AActor* Actor : TeleportList)
    {
        TeleportActor(Actor);
    }
}

FVector APortal::GetActorFrontPos(AActor* Actor) const
{
    if (!IsValid(Actor))
    {
        return FVector::ZeroVector;
    }

    // プレイヤーの向きに関係なく中心位置を使用
    return Actor->GetActorLocation();
}

FVector APortal::GetPlanePos() const
{
    return GetActorLocation()
        + GetActorForwardVector() * PortalPlaneOffset;
}

float APortal::GetSide(const FVector& Pos) const
{
    return FVector::DotProduct(
        Pos - GetPlanePos(),
        GetActorForwardVector());
}

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


void APortal::TeleportActor(AActor* Actor)
{
    if (!IsValid(Actor) || !IsValid(LinkedPortal))
    {
        UE_LOG(LogTemp, Error, TEXT("TeleportActor: Actor or LinkedPortal is invalid"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("TeleportActor: Start Actor=%s"), *Actor->GetName());

    const FTransform This = GetActorTransform();
    const FTransform Target = LinkedPortal->GetActorTransform();

    // ワープ元から見た相対位置を取得
    FTransform Local =
        Actor->GetActorTransform().GetRelativeTransform(This);

    // ワープ先の座標に変換
    FTransform NewWorld = Local * Target;

    FVector NewLocation = NewWorld.GetLocation();
    NewLocation += LinkedPortal->GetActorForwardVector() * 100.f;

    FRotator NewRotation = NewWorld.GetRotation().Rotator();

    bool bTeleported = false;

    if (ACharacter* Char = Cast<ACharacter>(Actor))
    {
        bTeleported = Char->TeleportTo(NewLocation, NewRotation, false, false);

        if (bTeleported)
        {
            FVector Vel = Char->GetCharacterMovement()->Velocity;

            FVector LocalVel = This.InverseTransformVector(Vel);
            FVector NewVel = Target.TransformVector(LocalVel);

            Char->GetCharacterMovement()->Velocity = NewVel;
        }
    }
    else
    {
        bTeleported = Actor->SetActorLocationAndRotation(NewLocation, NewRotation);
    }

    // テレポートに失敗した場合は後続処理を行わない
    if (!bTeleported)
    {
        UE_LOG(LogTemp, Error, TEXT("TeleportActor: Teleport failed!"));
        return;
    }

    // ワープループ防止
    RecentlyTeleported.Add(Actor);
    LinkedPortal->RecentlyTeleported.Add(Actor);

    // ワープ先の位置情報を更新
    LinkedPortal->OverlappingActors.Add(Actor);
    LinkedPortal->LastPos.FindOrAdd(Actor) =
        LinkedPortal->GetActorFrontPos(Actor);

    // 一定時間後にロック解除
    FTimerHandle Timer;

    GetWorld()->GetTimerManager().SetTimer(
        Timer,
        FTimerDelegate::CreateUObject(this, &APortal::ResetTeleport, Actor),
        TeleportCooldown, false);
}

void APortal::ResetTeleport(AActor* Actor)
{
    if (!IsValid(Actor))
    {
        RecentlyTeleported.Remove(Actor);

        if (LinkedPortal)
        {
            LinkedPortal->RecentlyTeleported.Remove(Actor);
        }

        return;
    }

    // ワープ元のロック解除
    RecentlyTeleported.Remove(Actor);

    // ワープ元の現在位置を更新
    LastPos.FindOrAdd(Actor) = GetActorFrontPos(Actor);

    if (LinkedPortal)
    {
        // ワープ先のロック解除
        LinkedPortal->RecentlyTeleported.Remove(Actor);

        // ワープ先の現在位置を更新
        LinkedPortal->LastPos.FindOrAdd(Actor) =
            LinkedPortal->GetActorFrontPos(Actor);

        LinkedPortal->OverlappingActors.Add(Actor);
    }
}


// ポータル移動前に呼ぶ
// ============================================================
// 9. ポータル移動前後のOverlap・衝突管理
// ============================================================

void APortal::PrepareForRelocation()
{
    RestoreOverlappingCollision();
}

void APortal::OnOverlap(
    UPrimitiveComponent*,
    AActor* OtherActor,
    UPrimitiveComponent*,
    int32,
    bool,
    const FHitResult&)
{
    if (!IsValid(OtherActor)) return;

    OverlappingActors.Add(OtherActor);
    LastPos.FindOrAdd(OtherActor) = GetActorFrontPos(OtherActor);

    if (ACharacter* Char = Cast<ACharacter>(OtherActor))
    {
        UCapsuleComponent* Capsule = Char->GetCapsuleComponent();

        if (Capsule)
        {
            // 元の設定を保存
            if (!OriginalWorldStaticResponses.Contains(OtherActor))
            {
                OriginalWorldStaticResponses.Add(
                    OtherActor,
                    Capsule->GetCollisionResponseToChannel(ECC_WorldStatic)
                );
            }

            // ポータル内では一時的に無視
            Capsule->SetCollisionResponseToChannel(
                ECC_WorldStatic,
                ECR_Ignore
            );
        }
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
        UCapsuleComponent* Capsule = Char->GetCapsuleComponent();

        if (Capsule)
        {
            // 保存していた元の設定に戻す
            if (ECollisionResponse* Original =
                OriginalWorldStaticResponses.Find(OtherActor))
            {
                Capsule->SetCollisionResponseToChannel(
                    ECC_WorldStatic,
                    *Original
                );
            }
        }
    }

    OriginalWorldStaticResponses.Remove(OtherActor);
}

void APortal::RestoreOverlappingCollision()
{
    for (const auto& Pair : OriginalWorldStaticResponses)
    {
        ACharacter* Char = Cast<ACharacter>(Pair.Key);

        if (!IsValid(Char)) continue;

        UCapsuleComponent* Capsule = Char->GetCapsuleComponent();

        if (Capsule)
        {
            Capsule->SetCollisionResponseToChannel(
                ECC_WorldStatic,
                Pair.Value
            );
        }
    }

    OriginalWorldStaticResponses.Empty();
    OverlappingActors.Empty();
    LastPos.Empty();
}

// ポータル破棄時にも復元
// ============================================================
// 10. 終了処理
// ============================================================

void APortal::EndPlay(
    const EEndPlayReason::Type EndPlayReason)
{
    RestoreOverlappingCollision();

    Super::EndPlay(EndPlayReason);
}