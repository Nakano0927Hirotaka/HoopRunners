#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/DecalComponent.h"
#include "PortalShooter.generated.h"

class APortal;

UCLASS()
class HOOPRUNNERS_API APortalShooter : public AActor
{
    GENERATED_BODY()

public:
    APortalShooter();

    UFUNCTION(BlueprintCallable, Category = "Fire")
    void Fire(FVector Start, FVector Forward);

    UFUNCTION(Server, Reliable)
    void ServerFire(FVector Start, FVector Forward);

    UFUNCTION(BlueprintCallable, Category = "UpdatePreview")
    void UpdatePreview(FVector Start, FVector Forward);

    UPROPERTY(EditAnywhere)
    TSubclassOf<APortal> PortalClass;


    // プレビュー用Actor
    UPROPERTY(EditAnywhere)
    TSubclassOf<AActor> ValidPreviewActor;

    UPROPERTY(EditAnywhere)
    TSubclassOf<AActor> InvalidPreviewActor;

    UPROPERTY(EditAnywhere, Category = "CellSize")
    float CellSize = 100.f; // ← 1マスの厚さ

    UPROPERTY(EditAnywhere, Category = "Portal")
    float PortalOffset = 10.f;

    UPROPERTY(EditAnywhere)
    UTextureRenderTarget2D* RT_PortalA;

    UPROPERTY(EditAnywhere)
    UTextureRenderTarget2D* RT_PortalB;

private:

    UPROPERTY()
    APortal* CurrentPortalA;

    UPROPERTY()
    APortal* CurrentPortalB;

    // プレビュー管理
    UPROPERTY()
    AActor* CurrentPreviewActor;

    bool bLastCanPlace = false;
};

