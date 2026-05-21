// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item_EMP.generated.h"

UCLASS()
class HOOP_RUNNERS_API AItem_EMP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem_EMP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void ActivateEMP();

	UPROPERTY(EditAnywhere)
	float StunDuration = 4.0f;

};
