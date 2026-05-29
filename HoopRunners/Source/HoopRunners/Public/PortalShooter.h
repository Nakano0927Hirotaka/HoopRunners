// PortalShooter.h

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

    UFUNCTION(BlueprintCallable, Category = "Portal")
    void Fire(FVector Start, FVector Forward);

    UFUNCTION(Server, Reliable)
    void ServerFire(FVector Start, FVector Forward);

    void ServerFire_Implementation(
        FVector Start,
        FVector Forward);

    void FireInternal(
        FVector Start,
        FVector Forward);

    UFUNCTION(BlueprintCallable, Category = "Portal")
    void UpdatePreview(
        FVector Start,
        FVector Forward);

public:

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

    // Preview
    UPROPERTY(EditAnywhere)
    TSubclassOf<AActor> ValidPreviewActor;

    UPROPERTY(EditAnywhere)
    TSubclassOf<AActor> InvalidPreviewActor;

private:

    UPROPERTY()
    APortal* CurrentPortalA;

    UPROPERTY()
    APortal* CurrentPortalB;

    UPROPERTY()
    AActor* CurrentPreviewActor;

    bool bLastCanPlace = false;
};