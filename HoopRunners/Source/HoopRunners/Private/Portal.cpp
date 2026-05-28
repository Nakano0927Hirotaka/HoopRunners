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

// ポータル平面を少し前にずらす距離
static constexpr float PortalPlaneOffset = 10.f;

// テレポート直後の再テレポート防止時間
static constexpr float TeleportCooldown = 0.05f;

// ===== Constructor =====

APortal::APortal()
{
    // Tick関数を毎フレーム呼ぶ
    PrimaryActorTick.bCanEverTick = true;

    // ネットワーク同期を有効化
    bReplicates = true;

    // Actorの移動情報も同期
    SetReplicateMovement(true);

    // ルートコンポーネント生成
    Root =
        CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    RootComponent = Root;

    // ポータル描画用カメラ生成
    Capture =
        CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture"));

    Capture->SetupAttachment(Root);

    if (Capture)
    {
        // 毎フレーム自動描画しない
        Capture->bCaptureEveryFrame = false;

        // 移動時の自動描画もしない
        Capture->bCaptureOnMovement = false;

        // RenderTargetを設定
        Capture->TextureTarget = RenderTarget;
    }

    // 当たり判定用Box生成
    Trigger =
        CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

    Trigger->SetupAttachment(Root);

    // ポータル範囲設定
    Trigger->SetBoxExtent(FVector(30.f, 100.f, 100.f));

    // ポータル見た目用メッシュ
    PortalMesh =
        CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));

    PortalMesh->SetupAttachment(Root);

    PrimaryActorTick.TickInterval = 0.03f;
}

// ===== BeginPlay =====

void APortal::BeginPlay()
{
    Super::BeginPlay();

    // 所有者確認ログ
    UE_LOG(LogTemp, Warning,
        TEXT("Owner = %s"),
        *GetNameSafe(GetOwner()));

    UE_LOG(LogTemp, Warning,
        TEXT("ShooterOwner=%s"),
        *GetNameSafe(GetOwner()));

    // マテリアルインスタンス生成
    if (PortalBaseMaterial)
    {
        PortalMID =
            UMaterialInstanceDynamic::Create(
                PortalBaseMaterial,
                this
            );

        // ポータルメッシュへ適用
        PortalMesh->SetMaterial(0, PortalMID);
    }

    // RenderTarget設定
    if (Capture && RenderTarget)
    {
        Capture->TextureTarget = RenderTarget;
    }

    // シーン全体を描画するモード
    Capture->PrimitiveRenderMode =
        ESceneCapturePrimitiveRenderMode::PRM_RenderScenePrimitives;

    // 自分自身のメッシュは映さない
    Capture->HideComponent(PortalMesh);

    // このActor全体を非表示
    Capture->HideActorComponents(this);

    Capture->ShowFlags.Atmosphere = false;
    Capture->ShowFlags.Fog = false;
    Capture->ShowFlags.MotionBlur = false;


    // TriggerはOverlap専用
    Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    Trigger->SetCollisionObjectType(ECC_WorldDynamic);

    // 全て無視
    Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);

    // PawnのみOverlap
    Trigger->SetCollisionResponseToChannel(
        ECC_Pawn,
        ECR_Overlap
    );

    // Overlap開始イベント登録
    Trigger->OnComponentBeginOverlap.AddDynamic(
        this,
        &APortal::OnOverlap
    );

    // Overlap終了イベント登録
    Trigger->OnComponentEndOverlap.AddDynamic(
        this,
        &APortal::OnEndOverlap
    );

}

// ===== Tick =====
void APortal::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // サーバーのみ実行
    if (HasAuthority())
    {
        // 無効Actor削除
        CleanupTimer += DeltaTime;

        if (CleanupTimer >= 2.f)
        {
            CleanupInvalidActors();
            CleanupTimer = 0.f;
        }

        // テレポート処理
        ProcessTeleport();
    }

    // DedicatedServer以外で描画更新
    if (!IsNetMode(NM_DedicatedServer))
    {
        UpdateCaptureCamera();
    }
}

// 無効になったActor情報を削除
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

// ポータルカメラ更新
void APortal::UpdateCaptureCamera()
{
    // 更新可能か確認
    if (!CanUpdateCamera())
    {
        return;
    }

    if (!PortalMesh->WasRecentlyRendered(0.1f))
    {
        return;
    }

    APawn* Pawn = ViewingPlayer->GetPawn();

    if (!Pawn)
    {
        return;
    }
    float Dist =
        FVector::Dist(
            Pawn->GetActorLocation(),
            GetActorLocation()
        );

    if (Dist > 2500.f)
    {
        return;
    }

    // ClipPlane設定
    SetupClipPlane();

    // デバッグ描画
    //DrawPortalDebug();

    // リンク先ポータル前方にカメラ配置
    FVector CamLocation =
        LinkedPortal->GetActorLocation()
        + LinkedPortal->GetActorForwardVector() * 10.f;

    // リンク先ポータル回転取得
    FRotator CamRotation =
        LinkedPortal->GetActorRotation();

    // カメラ位置設定
    if (!CamLocation.Equals(
        Capture->GetComponentLocation(), 1.f))
    {
        Capture->SetWorldLocation(CamLocation);
    }

    // カメラ回転設定
    if (!CamRotation.Equals(
        Capture->GetComponentRotation(), 1.f))
    {
        Capture->SetWorldRotation(CamRotation);
    }

    // シーン描画
    Capture->CaptureScene();
}

// カメラ更新可能か確認
bool APortal::CanUpdateCamera() const
{
    // リンク先やCapture未設定なら不可
    if (!LinkedPortal || !Capture)
    {
        return false;
    }

    // プレイヤー未設定
    if (!ViewingPlayer)
    {
        return false;
    }

    // ローカルプレイヤーのみ
    if (!ViewingPlayer->IsLocalController())
    {
        return false;
    }

    return true;
}

// ClipPlane設定
void APortal::SetupClipPlane()
{
    // ClipPlane有効化
    Capture->bEnableClipPlane = true;

    // 切断位置
    Capture->ClipPlaneBase =
        LinkedPortal->GetActorLocation();

    // 切断方向
    Capture->ClipPlaneNormal =
        LinkedPortal->GetActorForwardVector();
}

// デバッグ描画
void APortal::DrawPortalDebug()
{
    // メインポータルで色変更
    FColor DebugColor =
        bMainPortal ?
        FColor::Red :
        FColor::Blue;

    // Capture位置描画
    DrawDebugSphere(
        GetWorld(),
        Capture->GetComponentLocation(),
        30.f,
        12,
        DebugColor,
        false,
        0.f
    );

    // Forward方向描画
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

// テレポート判定処理
void APortal::ProcessTeleport()
{
    if (OverlappingActors.Num() == 0)
    {
        return;
    }

    TArray<AActor*> TeleportList;

    for (AActor* Actor : OverlappingActors)
    {
        // テレポート可能か確認
        if (!CanTeleport(Actor))
        {
            continue;
        }

        // 現在位置取得
        FVector CurrFront =
            GetActorFrontPos(Actor);

        // 初回登録
        if (!LastPos.Contains(Actor))
        {
            LastPos.Add(Actor, CurrFront);
            continue;
        }

        // 前フレーム位置
        FVector PrevFront =
            LastPos[Actor];

        // 前回の平面位置
        float PrevSide =
            GetSide(PrevFront);

        // 現在の平面位置
        float CurrSide =
            GetSide(CurrFront);

        // 平面を跨いだか判定
        if (PrevSide * CurrSide < 0.f)
        {
            // ポータル範囲内のみ
            if (IsInsidePortalBounds(CurrFront))
            {
                TeleportList.Add(Actor);
            }
        }

        // 位置更新
        LastPos[Actor] = CurrFront;
    }

    // テレポート実行
    for (AActor* Actor : TeleportList)
    {
        TeleportActor(Actor);
    }
}

// Actor前方位置取得
FVector APortal::GetActorFrontPos(AActor* Actor) const
{
    // Characterの場合
    if (ACharacter* Char = Cast<ACharacter>(Actor))
    {
        // カプセル半径取得
        float Radius =
            Char->GetCapsuleComponent()
            ->GetScaledCapsuleRadius();

        // 前方端位置を返す
        return
            Actor->GetActorLocation() +
            Actor->GetActorForwardVector() * Radius;
    }

    // 通常Actor
    return Actor->GetActorLocation();
}

// ポータル平面位置取得
FVector APortal::GetPlanePos() const
{
    return
        GetActorLocation() +
        GetActorForwardVector() * PortalPlaneOffset;
}

// 平面前後判定
float APortal::GetSide(const FVector& Pos) const
{
    return FVector::DotProduct(
        Pos - GetPlanePos(),
        GetActorForwardVector()
    );
}

// ポータル範囲内判定
bool APortal::IsInsidePortalBounds(const FVector& WorldPos) const
{
    // ローカル座標変換
    FVector Local =
        GetActorTransform()
        .InverseTransformPosition(WorldPos);

    FVector Extent = Trigger->GetScaledBoxExtent();

    // Y,Z範囲判定
    return
        FMath::Abs(Local.Y) <= Extent.Y &&
        FMath::Abs(Local.Z) <= Extent.Z;
}

// テレポート可能か
bool APortal::CanTeleport(AActor* Actor) const
{
    if (!IsValid(Actor)) return false;

    // クールタイム中
    if (RecentlyTeleported.Contains(Actor))
    {
        return false;
    }

    // リンク先なし
    if (!LinkedPortal)
    {
        return false;
    }

    return true;
}

// テレポート実行
void APortal::TeleportActor(AActor* Actor)
{
    if (!Actor || !LinkedPortal)
    {
        return;
    }

    const FTransform PortalTransform =
        GetActorTransform();

    // 現在ポータルTransform
    const FTransform This =
        PortalTransform;

    // リンク先Transform
    const FTransform Target =
        LinkedPortal->GetActorTransform();

    // ローカル変換
    FTransform Local =
        Actor->GetActorTransform()
        .GetRelativeTransform(This);

    // 新しいワールドTransform
    FTransform NewWorld =
        Local * Target;

    FVector NewLocation =
        NewWorld.GetLocation();

    // 少し前へ押し出す
    NewLocation +=
        LinkedPortal->GetActorForwardVector() * 50.f;

    // CharacterならTeleportTo
    if (ACharacter* Char = Cast<ACharacter>(Actor))
    {
        Char->TeleportTo(
            NewLocation,
            NewWorld.GetRotation().Rotator()
        );
    }
    else
    {
        // 通常Actor
        Actor->SetActorLocationAndRotation(
            NewLocation,
            NewWorld.GetRotation().Rotator()
        );
    }

    // リンク先Overlapへ追加
    LinkedPortal->OverlappingActors.Add(Actor);

    // 新しい位置登録
    LinkedPortal->LastPos.FindOrAdd(Actor) =
        LinkedPortal->GetActorFrontPos(Actor);

    // Character速度変換
    if (ACharacter* Char = Cast<ACharacter>(Actor))
    {
        FVector Vel =
            Char->GetCharacterMovement()->Velocity;

        // ローカル速度へ変換
        FVector LocalVel =
            This.InverseTransformVector(Vel);

        // 新ポータル方向へ変換
        FVector NewVel =
            Target.TransformVector(LocalVel);

        // 速度適用
        Char->GetCharacterMovement()->Velocity =
            NewVel;
    }

    // クールタイム登録
    RecentlyTeleported.Add(Actor);

    FTimerHandle Timer;

    // 一定時間後クールタイム解除
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

// テレポート状態リセット
void APortal::ResetTeleport(AActor* Actor)
{
    RecentlyTeleported.Remove(Actor);

    if (!Actor) return;

    FVector Front =
        GetActorFrontPos(Actor);

    // 現在位置更新
    LastPos.FindOrAdd(Actor) = Front;

    if (LinkedPortal)
    {
        LinkedPortal->LastPos.FindOrAdd(Actor) =
            Front;

        LinkedPortal->OverlappingActors.Add(Actor);
    }
}

// ===== Initialize =====

// ポータル初期化
void APortal::InitializePortal()
{
    if (!LinkedPortal || !Capture) return;

    // RenderTarget設定
    if (RenderTarget)
    {
        Capture->TextureTarget = RenderTarget;
    }

    // マテリアルへTexture設定
    if (PortalMID && LinkedPortal->RenderTarget)
    {
        PortalMID->SetTextureParameterValue(
            TEXT("PortalTexture"),
            RenderTarget
        );
    }

    // Capture位置
    FVector Pos =
        LinkedPortal->GetActorLocation()
        + LinkedPortal->GetActorForwardVector() * 20.f;

    // Capture回転
    FRotator Rot =
        LinkedPortal->GetActorRotation();

    Capture->SetWorldLocation(Pos);

    Capture->SetWorldRotation(Rot);

    Capture->TextureTarget = RenderTarget;

    // デバッグログ
    UE_LOG(LogTemp, Warning,
        TEXT("Portal=%s RT=%s Linked=%s"),
        *GetName(),
        *GetNameSafe(RenderTarget),
        *GetNameSafe(LinkedPortal)
    );
}

// 観測プレイヤー設定
void APortal::SetViewingPlayer(APlayerController* PC)
{
    ViewingPlayer = PC;
}

// レプリケーション設定
void APortal::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps
) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // LinkedPortal同期
    DOREPLIFETIME(APortal, LinkedPortal);
}

// ===== Overlap =====

// Overlap開始
void APortal::OnOverlap(
    UPrimitiveComponent*,
    AActor* OtherActor,
    UPrimitiveComponent*,
    int32,
    bool,
    const FHitResult&)
{
    if (!OtherActor) return;

    // 重なりActor登録
    OverlappingActors.Add(OtherActor);

    // 初期位置保存
    LastPos.FindOrAdd(OtherActor) =
        GetActorFrontPos(OtherActor);

    // Characterの壁衝突を無効化
    if (ACharacter* Char = Cast<ACharacter>(OtherActor))
    {
        Char->GetCapsuleComponent()
            ->SetCollisionResponseToChannel(
                ECC_WorldStatic,
                ECR_Ignore
            );
    }
}

// Overlap終了
void APortal::OnEndOverlap(
    UPrimitiveComponent*,
    AActor* OtherActor,
    UPrimitiveComponent*,
    int32)
{
    if (!OtherActor) return;

    // 管理リスト削除
    OverlappingActors.Remove(OtherActor);

    LastPos.Remove(OtherActor);

    // 壁衝突を元に戻す
    if (ACharacter* Char = Cast<ACharacter>(OtherActor))
    {
        Char->GetCapsuleComponent()
            ->SetCollisionResponseToChannel(
                ECC_WorldStatic,
                ECR_Block
            );
    }
}