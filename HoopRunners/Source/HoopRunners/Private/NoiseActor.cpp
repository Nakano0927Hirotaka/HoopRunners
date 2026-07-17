
#include "NoiseActor.h"
#include "DrawDebugHelpers.h"

ANoiseActor::ANoiseActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ANoiseActor::BeginPlay()
{
    Super::BeginPlay();

    SetLifeSpan(Duration);

    DrawDebugSphere(
        GetWorld(),
        GetActorLocation(),
        Radius,
        32,
        FColor::Red,
        false,
        Duration
    );
}