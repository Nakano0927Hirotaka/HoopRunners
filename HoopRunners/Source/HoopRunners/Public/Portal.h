#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// ネットワーク同期関連
#include "Net/UnrealNetwork.h"

#include "Portal.generated.h"

// ===== 前方宣言 =====

// Box当たり判定
class UBoxComponent;

// ポータル表示用メッシュ
class UStaticMeshComponent;

// 動的マテリアル
class UMaterialInstanceDynamic;

// ポータル描画用カメラ
class USceneCaptureComponent2D;

// 描画先テクスチャ
class UTextureRenderTarget2D;

// プレイヤー操作クラス
class APlayerController;


class USceneComponent;

UCLASS()
class HOOPRUNNERS_API APortal : public AActor
{
    GENERATED_BODY()

public:

    //==================================================
    // Portal Settings
    //==================================================

    // ポータル描画先RenderTarget
    UPROPERTY(EditAnywhere, Category = "Portal")
    UTextureRenderTarget2D* RenderTarget;

    // メインポータルか判定
    UPROPERTY(EditAnywhere, Category = "Portal")
    bool bMainPortal = false;

    // コンストラクタ
    APortal();

    // 毎フレーム更新
    virtual void Tick(float DeltaTime) override;

    // ポータル初期化
    void InitializePortal();

    // 描画用プレイヤー設定
    void SetViewingPlayer(APlayerController* PC);

    // 接続先ポータル
    UPROPERTY(Replicated)
    APortal* LinkedPortal;

protected:

    // BeginPlay
    virtual void BeginPlay() override;

    float CleanupTimer = 0.f;

    //==================================================
    // Components
    //==================================================

    // ルートコンポーネント
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;

    // Overlap判定用Box
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* Trigger;

    // ポータル描画用カメラ
    UPROPERTY(VisibleAnywhere)
    USceneCaptureComponent2D* Capture;

    // ポータル見た目メッシュ
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* PortalMesh;

    //==================================================
    // Materials
    //==================================================

    // ベースマテリアル
    UPROPERTY(EditAnywhere)
    UMaterialInterface* PortalBaseMaterial;

    // 動的マテリアルインスタンス
    UPROPERTY()
    UMaterialInstanceDynamic* PortalMID;

    //==================================================
    // Player
    //==================================================

    // このポータルを見るプレイヤー
    UPROPERTY()
    APlayerController* ViewingPlayer;

    //==================================================
    // Teleport State
    //==================================================

    // Actorの前フレーム位置保存
    UPROPERTY()
    TMap<AActor*, FVector> LastPos;

    // 現在ポータル内にいるActor
    UPROPERTY()
    TSet<AActor*> OverlappingActors;

    // テレポート直後Actor
    UPROPERTY()
    TSet<AActor*> RecentlyTeleported;

    //==================================================
    // Main Update
    //==================================================

    // 無効Actor削除
    void CleanupInvalidActors();

    // ポータル描画更新
    void UpdateCaptureCamera();

    // テレポート判定処理
    void ProcessTeleport();

    //==================================================
    // Camera
    //==================================================

    // カメラ更新可能か
    bool CanUpdateCamera() const;

    // ClipPlane設定
    void SetupClipPlane();

    // デバッグ描画
    void DrawPortalDebug();

    //==================================================
    // Portal Checks
    //==================================================

    // ポータル平面の前後判定
    float GetSide(const FVector& Pos) const;

    // ポータル平面位置取得
    FVector GetPlanePos() const;

    // Actor前方位置取得
    FVector GetActorFrontPos(AActor* Actor) const;

    // ポータル範囲内判定
    bool IsInsidePortalBounds(const FVector& WorldPos) const;

    // テレポート可能判定
    bool CanTeleport(AActor* Actor) const;

    //==================================================
    // Teleport
    //==================================================

    // テレポート実行
    void TeleportActor(AActor* Actor);

    // テレポート状態解除
    void ResetTeleport(AActor* Actor);

    //==================================================
    // Overlap
    //==================================================

    // ポータル侵入時
    UFUNCTION()
    void OnOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    // ポータル退出時
    UFUNCTION()
    void OnEndOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex
    );
};