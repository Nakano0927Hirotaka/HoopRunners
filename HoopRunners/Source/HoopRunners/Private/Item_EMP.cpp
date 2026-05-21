// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_EMP.h"
#include "EnemyCharacter.h"
#include "EngineUtils.h"

// Sets default values
AItem_EMP::AItem_EMP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AItem_EMP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem_EMP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem_EMP::ActivateEMP()
{
	for (TActorIterator<AEnemyCharacter>It(GetWorld()); It; ++It)
	{
		AEnemyCharacter* Enemy = *It;

		if (Enemy)
		{
			Enemy->ApplyEMP(StunDuration);
		}
	}

	Destroy();

}