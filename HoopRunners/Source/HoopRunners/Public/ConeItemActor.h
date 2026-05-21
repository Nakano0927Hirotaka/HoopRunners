// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConeItemActor.generated.h"

UCLASS()
class HOOP_RUNNERS_API AConeItemActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AConeItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void UpdateItemDisplay();

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static int32 CollectedItemCount;

	static const int32 MaxItemCount = 10;

};
