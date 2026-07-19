// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyCharacter.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Patrol,
	Chase,
	FullChase,
	Capture
};

UCLASS()
class HOOPRUNNERS_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	bool bHasPatrolTarget;

	UFUNCTION(BlueprintCallable)
	void ApplyEMP(float StunDuration);

	FVector CurrentPatrolLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//AI Perception
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* AIPerception;

	UPROPERTY()
	UAISenseConfig_Sight* SightConfig;

	//現在ステート
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEnemyState CurrentState;

	//現在ターゲット
	UPROPERTY()
	AActor* CurrentTarget;

	//檻座標
	UPROPERTY(EditAnywhere, Category = "Capture")
	FVector CageLocation;

	//宝石の数
	UPROPERTY(EditAnywhere)
	int32 GemThreshold = 10;

	//時間条件
	UPROPERTY(EditAnywhere)
	float FullChaseStartTime = 900.0f;

	float LastSeenTime = -1000.0f;

	float DefaultSightRadius;
	float DefaultLoseSightRadius;

	//スタン中か
	bool bIsStunned;

	//スタンタイマー
	FTimerHandle StunTimerHandle;

	//スタン解除
	void EndStun();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float LoseSightChaseDuration = 5.0f;

	void SetInfiniteSight(bool bEnable);

	//視界更新
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	//巡回
	void Patrol();

	//通常追跡
	void Chase();

	//完全追跡
	void FullChase();

	//捕獲
	void CapturePlayer(ACharacter* Player);

	//状態更新
	void UpdateState();

	//接触判定
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
