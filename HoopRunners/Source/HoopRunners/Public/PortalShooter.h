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


    // ========================================
    // 設置可能判定
    // ========================================

    UFUNCTION(BlueprintCallable, Category = "Portal")
    bool CanPlacePortal(
        FVector Start,
        FVector Forward,
        FVector& OutFrontLocation,
        FRotator& OutFrontRotation,
        FVector& OutBackLocation,
        FRotator& OutBackRotation);


    // ========================================
    // プレビュー
    // ========================================

    UFUNCTION(BlueprintCallable, Category = "Portal Preview")
    void StartPortalPreview();

    UFUNCTION(BlueprintCallable, Category = "Portal Preview")
    void StopPortalPreview();

    UFUNCTION(BlueprintCallable, Category = "Portal Preview")
    void UpdatePreview(
        FVector Start,
        FVector Forward);

    UFUNCTION(BlueprintPure, Category = "Portal Preview")
    bool IsPortalPlaceable() const;

    void UpdatePreviewColor();


public:

    // ========================================
    // Portal
    // ========================================

    UPROPERTY(EditAnywhere, Category = "Portal")
    TSubclassOf<APortal> PortalClass;

    UPROPERTY(EditAnywhere, Category = "Portal")
    float CellSize = 100.f;

    UPROPERTY(EditAnywhere, Category = "Portal")
    float PortalOffset = 10.f;

    UPROPERTY(EditAnywhere, Category = "Portal")
    UTextureRenderTarget2D* RT_PortalA;

    UPROPERTY(EditAnywhere, Category = "Portal")
    UTextureRenderTarget2D* RT_PortalB;


    // ========================================
    // Preview Class
    // ========================================

    UPROPERTY(EditAnywhere, Category = "Portal Preview")
    TSubclassOf<AActor> ValidPreviewClass;

    UPROPERTY(EditAnywhere, Category = "Portal Preview")
    TSubclassOf<AActor> InvalidPreviewClass;


private:

    // ========================================
    // 現在のポータル
    // ========================================

    UPROPERTY()
    APortal* CurrentPortalA;

    UPROPERTY()
    APortal* CurrentPortalB;


    // ========================================
    // プレビューActor
    // ========================================

    UPROPERTY()
    AActor* ValidPreviewActor;

    UPROPERTY()
    AActor* InvalidPreviewActor;

    UPROPERTY()
    AActor* CurrentPreviewActor;


    // ========================================
    // 状態
    // ========================================

    bool bPreviewing = false;

    bool bCanPlacePortal = false;


    // ========================================
    // RT
    // ========================================

    UTextureRenderTarget2D* CreatePortalRT();
};