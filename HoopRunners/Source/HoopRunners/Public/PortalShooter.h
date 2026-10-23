#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalShooter.generated.h"

class APortal;
class UTextureRenderTarget2D;

UCLASS()
class HOOPRUNNERS_API APortalShooter : public AActor
{
    GENERATED_BODY()

public:

    APortalShooter();

    virtual void Tick(float DeltaTime) override;

    virtual void BeginPlay() override;


    // ========================================
    // ポータル設置
    // ========================================

    UFUNCTION(BlueprintCallable, Category = "Portal")
    void Fire(FVector Start, FVector Forward);

    UFUNCTION(Server, Reliable)
    void ServerFire(FVector Start, FVector Forward);

    void ServerFire_Implementation(
        FVector Start, FVector Forward);

    void FireInternal(FVector Start, FVector Forward);

    // 残りクールタイムを取得
    UFUNCTION(BlueprintPure, Category = "Portal")
    float GetRemainingCooldown() const;

    // ポータルを設置できるか
    UFUNCTION(BlueprintPure, Category = "Portal")
    bool IsPortalReady() const;

    // クールタイムの進行率（0.0～1.0）
    UFUNCTION(BlueprintPure, Category = "Portal|Cooldown")
    float GetCooldownProgress() const;

    virtual void GetLifetimeReplicatedProps(
        TArray<FLifetimeProperty>& OutLifetimeProps
    ) const override;

    static float GetPortalGameTime(const UWorld* World);

    // ========================================
    // 設置可能判定
    // ========================================

    UFUNCTION(BlueprintCallable, Category = "Portal")
    bool CanPlacePortal(FVector Start, FVector Forward, 
        FVector& OutFrontLocation, FRotator& OutFrontRotation, 
        FVector& OutBackLocation, FRotator& OutBackRotation);

    // ========================================
    // プレビュー
    // ========================================

    UFUNCTION(BlueprintCallable, Category = "Portal Preview")
    void StartPortalPreview();

    UFUNCTION(BlueprintCallable, Category = "Portal Preview")
    void StopPortalPreview();

    UFUNCTION(BlueprintCallable, Category = "Portal Preview")
    void UpdatePreview(FVector Start, FVector Forward);

    UFUNCTION(BlueprintPure, Category = "Portal Preview")
    bool IsPortalPlaceable() const;

    void UpdatePreviewColor();

    // ========================================
    // RT
    // ========================================
    UTextureRenderTarget2D* CreatePortalRT();

public:

    // ========================================
    // Portal
    // ========================================

    UPROPERTY(EditAnywhere, Category = "Portal")
    TSubclassOf<APortal> PortalClass;

    // ポータルのクールタイム
    UPROPERTY(EditAnywhere, Category = "Portal")
    float PortalCooldown = 3.0f;

    // 壁の厚さ
    UPROPERTY(EditAnywhere, Category = "Portal")
    float CellSize = 100.f;

    // ポータルと壁の距離
    UPROPERTY(EditAnywhere, Category = "Portal")
    float PortalOffset = 10.f;

    // 床からポータル中心までの高さ（cm）
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal")
    float PortalHeightFromFloor = 200.0f;

    UPROPERTY(EditAnywhere, Category = "Portal")
    UTextureRenderTarget2D* RT_PortalA;

    UPROPERTY(EditAnywhere, Category = "Portal")
    UTextureRenderTarget2D* RT_PortalB;

    // Preview Class
    // 表示するプレビューのクラス
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal Preview")
    TSubclassOf<AActor> ValidPreviewClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal Preview")
    TSubclassOf<AActor> InvalidPreviewClass;

    // 実際に生成されたプレビューアクター
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portal Preview")
    TObjectPtr<AActor> ValidPreviewActor = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portal Preview")
    TObjectPtr<AActor> InvalidPreviewActor = nullptr;


private:

    // ========================================
    // 現在のポータル
    // ========================================

    UPROPERTY()
    APortal* CurrentPortalA;

    UPROPERTY()
    APortal* CurrentPortalB;

    // ========================================
    // 次に設置可能になるゲーム内時刻
    // ========================================
    UPROPERTY(Replicated)
    float nextPortalTime = 0.0f;

    // ========================================
    // プレビューActor
    // ========================================

    UPROPERTY()
    AActor* CurrentPreviewActor;

    // ========================================
    // 状態
    // ========================================

    bool bPreviewing = false;

    bool bCanPlacePortal = false;

};