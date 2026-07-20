
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoiseActor.generated.h"

UCLASS()
class HOOPRUNNERS_API ANoiseActor : public AActor
{
    GENERATED_BODY()

public:
    ANoiseActor();

protected:
    virtual void BeginPlay() override;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
    float Radius = 500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
    float Duration = 10.f;
};