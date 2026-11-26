
#include "NoiseActor.h"
#include "DrawDebugHelpers.h"

ANoiseActor::ANoiseActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ANoiseActor::BeginPlay()
{
    Super::BeginPlay();

    ExpirationTime = GetWorld()->GetTimeSeconds() + FMath::Max(Duration, 0.0f);
    SetLifeSpan(FMath::Max(Duration, 0.01f));

    if (bDrawDebug)
    {
        DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 32, FColor::Red, false, Duration);
    }
}

float ANoiseActor::GetRemainingDuration() const
{
    return GetWorld() ? FMath::Max(0.0f, ExpirationTime - GetWorld()->GetTimeSeconds()) : 0.0f;
}
