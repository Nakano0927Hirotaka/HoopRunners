#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "Portal.generated.h"

// ===== 前方宣言 =====

// Overlap判定用Box
class UBoxComponent;

// ポータル見た目メッシュ
class UStaticMeshComponent;

// 動的マテリアルインスタンス
class UMaterialInstanceDynamic;

// ポータル描画用カメラ
class USceneCaptureComponent2D;

// 描画先テクスチャ
class UTextureRenderTarget2D;

// プレイヤー操作クラス
class APlayerController;

// ルートコンポーネント
class USceneComponent;

UCLASS()
class HOOPRUNNERS_API APortal : public AActor
{
    GENERATED_BODY()

public:

    // コンストラクタ
    APortal();

    // 毎フレーム更新
    virtual void Tick(float DeltaTime) override;

    // ポータル初期化（サーバーからMulticast_SetupRTを呼ぶ）
    void InitializePortal();

    // 描画対象プレイヤーを設定
    void SetViewingPlayer(APlayerController* PC);

    //==================================================
    // ネットワーク同期プロパティ
    //==================================================

    // リンク先ポータル（同期時にOnRep_LinkedPortalを呼ぶ）
    UPROPERTY(ReplicatedUsing = OnRep_LinkedPortal)
    APortal* LinkedPortal = nullptr;

    // このポータルを所有するプレイヤー
    UPROPERTY(Replicated)
    APlayerController* OwnerPlayer;

    // メインポータル（A側）かどうか
    UPROPERTY(EditAnywhere, Category = "Portal")
    bool bMainPortal = false;

    //==================================================
    // 描画用RT
    //==================================================

    // 自分のCaptureが書き込む先のRT
    // UpdateCaptureCameraでCaptureScene()するとここに描画される
    UPROPERTY()
    UTextureRenderTarget2D* CaptureRT = nullptr;

    // 自分のメッシュに表示するRT
    // リンク先のCaptureRTを受け取ってMIDに適用する
    UPROPERTY()
    UTextureRenderTarget2D* DisplayRT = nullptr;

    // ポータルメッシュの動的マテリアルインスタンス
    // DisplayRTをPortalTextureパラメータへ渡す
    UPROPERTY()
    UMaterialInstanceDynamic* PortalMID = nullptr;

    //==================================================
    // RPC
    //==================================================

    // サーバーから全クライアントへRTセットアップを命令する
    // InitializePortal()から呼ばれる
    UFUNCTION(NetMulticast, Reliable)
    void Multicast_SetupRT(bool bIsPortalA);

    // DisplayRTをMIDのPortalTextureパラメータへ適用する
    void ApplyDisplayRT();

protected:

    // 初期化処理
    virtual void BeginPlay() override;

    // CleanupInvalidActors呼び出し間隔計測用タイマー
    float CleanupTimer = 0.f;

    // Tickの累積時間（描画間引き用）
    float CaptureAccum = 0.f;

    //==================================================
    // コンポーネント
    //==================================================

    // ルートコンポーネント
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;

    // テレポート判定用Boxトリガー
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* Trigger;

    // ポータル映像を撮影するカメラ
    // リンク先ポータル付近に配置してCaptureRTへ書き込む
    UPROPERTY(VisibleAnywhere)
    USceneCaptureComponent2D* Capture;

    // ポータルの見た目メッシュ
    // DisplayRTを貼ったMIDを適用する
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* PortalMesh;

    // ポータルのベースマテリアル
    // BeginPlayでMIDを生成する元になる
    UPROPERTY(EditAnywhere)
    UMaterialInterface* PortalBaseMaterial;

    //==================================================
    // プレイヤー
    //==================================================

    // このポータルを見るプレイヤー
    // UpdateCaptureCameraでの距離判定に使用
    UPROPERTY()
    APlayerController* ViewingPlayer;

    //==================================================
    // テレポート管理
    //==================================================

    // Actorの前フレーム位置（平面跨ぎ判定に使用）
    UPROPERTY()
    TMap<AActor*, FVector> LastPos;

    // 現在ポータル内にいるActor一覧
    UPROPERTY()
    TSet<AActor*> OverlappingActors;

    // テレポート直後のActor（クールタイム管理）
    UPROPERTY()
    TSet<AActor*> RecentlyTeleported;

    //==================================================
    // OnRep
    //==================================================

    // LinkedPortalが同期された時に呼ばれる
    // CaptureRTが両方揃っていればDisplayRTを相互適用する
    UFUNCTION()
    void OnRep_LinkedPortal();

    //==================================================
    // 内部処理
    //==================================================

    // 無効になったActorをLastPos/OverlappingActorsから削除
    void CleanupInvalidActors();

    // Captureカメラを更新してCaptureScene()を呼ぶ
    void UpdateCaptureCamera();

    // ポータル平面を跨いだActorをテレポートする
    void ProcessTeleport();

    // カメラ更新が可能か確認
    // LinkedPortal/Capture/ViewingPlayer/TextureTargetの有無を確認
    bool CanUpdateCamera() const;

    // CaptureのClipPlaneをリンク先ポータル面に設定
    // リンク先より手前を描画しないようにする
    void SetupClipPlane();

    // デバッグ用描画（Capture位置・Forward方向）
    void DrawPortalDebug();

    // ポータル平面の前後を判定（正=表側、負=裏側）
    float GetSide(const FVector& Pos) const;

    // ポータル平面の基準位置を取得
    FVector GetPlanePos() const;

    // Actorの前方端位置を取得（Characterはカプセル半径分前方）
    FVector GetActorFrontPos(AActor* Actor) const;

    // WorldPosがポータルのY/Z範囲内にあるか判定
    bool IsInsidePortalBounds(const FVector& WorldPos) const;

    // テレポート可能か確認
    // 無効Actor/クールタイム中/LinkedPortalなしの場合はfalse
    bool CanTeleport(AActor* Actor) const;

    // Actorをリンク先ポータルへテレポートする
    void TeleportActor(AActor* Actor);

    // クールタイム終了後にRecentlyTeleportedから削除する
    void ResetTeleport(AActor* Actor);

    // UTextureRenderTarget2Dを1024x1024で生成する
    UTextureRenderTarget2D* CreateRT();

    // Triggerのコリジョン設定とOverlapイベントを登録する
    void SetupTrigger();

    //==================================================
    // Overlap
    //==================================================

    // ポータルにActorが入った時
    // OverlappingActorsへ追加し初期位置を保存する
    UFUNCTION()
    void OnOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

    // ポータルからActorが出た時
    // OverlappingActorsから削除しコリジョンを元に戻す
    UFUNCTION()
    void OnEndOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex);
};