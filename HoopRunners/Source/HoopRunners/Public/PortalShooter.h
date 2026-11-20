#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalShooter.generated.h"

class APortal;
class UTextureRenderTarget2D;

// ポータルの設置判定・生成・プレビュー・クールタイムを担当するActor
UCLASS()
class HOOPRUNNERS_API APortalShooter : public AActor
{
    GENERATED_BODY()

public:
    APortalShooter();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // ==================================================
    // 1. ポータル設置・生成
    // ==================================================
    UFUNCTION(BlueprintCallable, Category = "Portal")
    void Fire(FVector Start, FVector Forward);

    UFUNCTION(Server, Reliable)
    void ServerFire(FVector Start, FVector Forward);
    void ServerFire_Implementation(FVector Start, FVector Forward);
    void FireInternal(FVector Start, FVector Forward);

    UFUNCTION(BlueprintCallable, Category = "Portal")
    bool CanPlacePortal(FVector Start, FVector Forward, FVector& OutFrontLocation, FRotator& OutFrontRotation, FVector& OutBackLocation, FRotator& OutBackRotation);

    // ==================================================
    // 2. ポータル設置プレビュー
    // ==================================================
    UFUNCTION(BlueprintCallable, Category = "Portal Preview")
    void StartPortalPreview();

    UFUNCTION(BlueprintCallable, Category = "Portal Preview")
    void StopPortalPreview();

    UFUNCTION(BlueprintCallable, Category = "Portal Preview")
    void UpdatePreview(FVector Start, FVector Forward);

    UFUNCTION(BlueprintPure, Category = "Portal Preview")
    bool IsPortalPlaceable() const;

    void UpdatePreviewColor();

    // ==================================================
    // 3. クールタイム・ゲーム時刻
    // ==================================================
    UFUNCTION(BlueprintPure, Category = "Portal")
    float GetRemainingCooldown() const;

    UFUNCTION(BlueprintPure, Category = "Portal")
    bool IsPortalReady() const;

    UFUNCTION(BlueprintPure, Category = "Portal|Cooldown")
    float GetCooldownProgress() const;

    static float GetPortalGameTime(const UWorld* World);

    // ==================================================
    // 4. 描画用Render Target・ネットワーク同期
    // ==================================================
    UTextureRenderTarget2D* CreatePortalRT();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // ==================================================
    // 5. エディタ設定：ポータル本体
    // ==================================================
    UPROPERTY(EditAnywhere, Category = "Portal")
    TSubclassOf<APortal> PortalClass;

    UPROPERTY(EditAnywhere, Category = "Portal")
    float PortalCooldown = 3.0f;

    UPROPERTY(EditAnywhere, Category = "Portal")
    float CellSize = 100.f;

    UPROPERTY(EditAnywhere, Category = "Portal")
    float PortalOffset = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal")
    float PortalHeightFromFloor = 200.0f;

    // ==================================================
    // 6. エディタ設定：描画用RT
    // ==================================================
    UPROPERTY(EditAnywhere, Category = "Portal")
    UTextureRenderTarget2D* RT_PortalA;

    UPROPERTY(EditAnywhere, Category = "Portal")
    UTextureRenderTarget2D* RT_PortalB;

    // ==================================================
    // 7. エディタ設定：プレビュー表示
    // ==================================================
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal Preview")
    TSubclassOf<AActor> ValidPreviewClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal Preview")
    TSubclassOf<AActor> InvalidPreviewClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portal Preview")
    TObjectPtr<AActor> ValidPreviewActor = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portal Preview")
    TObjectPtr<AActor> InvalidPreviewActor = nullptr;

private:
    // ==================================================
    // 8. 実行中のポータル参照
    // ==================================================
    UPROPERTY()
    APortal* CurrentPortalA = nullptr;

    UPROPERTY()
    APortal* CurrentPortalB = nullptr;

    // ==================================================
    // 9. 実行中のプレビュー参照・状態
    // ==================================================
    UPROPERTY()
    AActor* CurrentPreviewActor = nullptr;

    bool bPreviewing = false;
    bool bCanPlacePortal = false;

    // ==================================================
    // 10. ネットワーク共有のクールタイム状態
    // ==================================================
    UPROPERTY(Replicated)
    float nextPortalTime = 0.0f;
};
