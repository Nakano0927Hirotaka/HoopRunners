#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "Portal.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UMaterialInstanceDynamic;
class USceneCaptureComponent2D;
class UTextureRenderTarget2D;
class APlayerController;

UCLASS()
class HOOPRUNNERS_API APortal : public AActor
{
    GENERATED_BODY()

public:
    //==================================================
    // Portal Settings
    //==================================================

    UPROPERTY(EditAnywhere, Category = "Portal")
    UTextureRenderTarget2D* RenderTarget;

    UPROPERTY(EditAnywhere, Category = "Portal")
    bool bMainPortal = false;

    APortal();

    virtual void Tick(float DeltaTime) override;

    void InitializePortal();

    void SetViewingPlayer(APlayerController* PC);

    UPROPERTY(Replicated)
    APortal* LinkedPortal;

protected:
    virtual void BeginPlay() override;

    //==================================================
    // Components
    //==================================================

    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* Trigger;

    UPROPERTY(VisibleAnywhere)
    USceneCaptureComponent2D* Capture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* PortalMesh;


    //==================================================
    // Materials
    //==================================================

    UPROPERTY(EditAnywhere)
    UMaterialInterface* PortalBaseMaterial;

    UPROPERTY()
    UMaterialInstanceDynamic* PortalMID;

    //==================================================
    // Player
    //==================================================

    UPROPERTY()
    APlayerController* ViewingPlayer;

    //==================================================
    // Teleport State
    //==================================================

    UPROPERTY()
    TMap<AActor*, FVector> LastPos;

    UPROPERTY()
    TSet<AActor*> OverlappingActors;

    UPROPERTY()
    TSet<AActor*> RecentlyTeleported;

    //==================================================
    // Main Update
    //==================================================

    void CleanupInvalidActors();

    void UpdateCaptureCamera();

    void ProcessTeleport();

    //==================================================
    // Camera
    //==================================================

    bool CanUpdateCamera() const;

    void SetupClipPlane();

    void DrawPortalDebug();

    //==================================================
    // Portal Checks
    //==================================================

    float GetSide(const FVector& Pos) const;

    FVector GetPlanePos() const;

    FVector GetActorFrontPos(AActor* Actor) const;

    bool IsInsidePortalBounds(const FVector& WorldPos) const;

    bool CanTeleport(AActor* Actor) const;

    //==================================================
    // Teleport
    //==================================================

    void TeleportActor(AActor* Actor);

    void ResetTeleport(AActor* Actor);

    //==================================================
    // Overlap
    //==================================================

    UFUNCTION()
    void OnOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    UFUNCTION()
    void OnEndOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex
    );
};