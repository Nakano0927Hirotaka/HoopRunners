#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class ANoiseActor;
class APawn;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Patrol,
	Chase,
	FullChase,
	Stun
};

// Server-authoritative main enemy. Clients receive movement and the visible state.
UCLASS(Blueprintable)
class HOOPRUNNERS_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category="AI")
	EEnemyState GetEnemyState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable, Category="AI")
	void ApplyEMP(float StunDuration = 5.0f);

	// Call from a server-side game event when full chase should start early.
	UFUNCTION(BlueprintCallable, Category="AI")
	void StartFullChase();

	// The rescue event can make a captured player targetable again.
	UFUNCTION(BlueprintCallable, Category="AI|Capture")
	void ReleaseCapturedPlayer(APawn* Player);

	// Call from the server-side gem pickup event if it does not update PlayerState.Jewly.
	UFUNCTION(BlueprintCallable, Category="AI|Full Chase")
	void NotifyGemCollected();

	// The future enemy-room event can call this once at its chosen spawn point.
	UFUNCTION(BlueprintCallable, Category="AI|Spawn", meta=(WorldContext="WorldContextObject"))
	static AEnemyCharacter* SpawnAdditionalMainEnemy(
		UObject* WorldContextObject, TSubclassOf<AEnemyCharacter> EnemyClass,
		const FTransform& SpawnTransform);

	// Retained for existing Blueprint references.
	bool bHasPatrolTarget = false;
	FVector CurrentPatrolLocation = FVector::ZeroVector;

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Kept for Blueprint component references; server sight decisions use explicit traces.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI|Vision")
	TObjectPtr<UAIPerceptionComponent> AIPerception;

	UPROPERTY()
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Movement", meta=(ClampMin="0.0"))
	float PatrolSpeed = 350.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Movement", meta=(ClampMin="0.0"))
	float ChaseSpeed = 700.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Vision", meta=(ClampMin="0.0"))
	float SightRange = 5000.0f;

	// Half of the 60-degree field of view.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Vision", meta=(ClampMin="1.0", ClampMax="89.0"))
	float SightHalfAngleDegrees = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Vision", meta=(ClampMin="0.05"))
	float SenseInterval = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Patrol", meta=(ClampMin="0.0"))
	float PatrolRadius = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Patrol", meta=(ClampMin="0.0"))
	float PatrolWaitMin = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Patrol", meta=(ClampMin="0.0"))
	float PatrolWaitMax = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Chase", meta=(ClampMin="0.0"))
	float LoseSightChaseDuration = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Chase", meta=(ClampMin="0.0"))
	float SearchTurnDegreesPerSecond = 120.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Capture", meta=(ClampMin="0.0"))
	float CaptureDistance = 200.0f;

	UPROPERTY(EditAnywhere, Category="AI|Capture")
	FVector CageLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category="AI|Capture")
	TObjectPtr<AActor> CageActor;

	// At three minutes, enter full chase only if nobody has collected a gem.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Full Chase", meta=(ClampMin="0.0"))
	float NoGemFullChaseDelaySeconds = 180.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Noise", meta=(ClampMin="0.0"))
	float EmittedNoiseRadius = 1200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Noise", meta=(ClampMin="0.0"))
	float EmittedNoiseDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Noise", meta=(ClampMin="0.05"))
	float EmittedNoiseInterval = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Noise", meta=(ClampMin="0.0"))
	float NoiseArrivalDistance = 200.0f;

	UPROPERTY(ReplicatedUsing=OnRep_CurrentState, VisibleAnywhere, BlueprintReadOnly, Category="AI")
	EEnemyState CurrentState = EEnemyState::Patrol;

	UFUNCTION()
	void OnRep_CurrentState();

	UFUNCTION(BlueprintImplementableEvent, Category="AI")
	void OnEnemyStateChanged(EEnemyState NewState);

	// Retained for existing Blueprint overlap bindings; distance is checked here too.
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnGemOverlap(AActor* GemActor, AActor* OtherActor);

	UFUNCTION()
	void OnCageEndOverlap(AActor* Cage, AActor* OtherActor);

private:
	void SetState(EEnemyState NewState);
	void GatherPlayers(TArray<APawn*>& OutPlayers) const;
	bool IsAvailablePlayer(const APawn* Player) const;
	APawn* FindNearestVisiblePlayer(FVector& OutLocation) const;
	APawn* FindNearestPlayer() const;
	AActor* FindBestAudibleNoise() const;
	bool IsPlayerNoise(const AActor* Noise) const;
	void NotifyPlayerNoiseDetected(AActor* Noise, float CurrentTime);
	void UpdateGemCollection();
	void RegisterGemActor(AActor* Actor);
	void OnActorSpawned(AActor* Actor);
	void UpdateSenses(float CurrentTime);
	void EnterPatrol();
	void TickPatrol(float CurrentTime, float DeltaTime);
	void TickChase(float CurrentTime, float DeltaTime);
	void TickFullChase(float CurrentTime);
	void ChoosePatrolPoint(float CurrentTime);
	bool RequestMove(const FVector& Destination, float CurrentTime, bool bForce = false);
	void TryCaptureNearbyPlayer();
	void CapturePlayer(APawn* Player);
	void EmitChaseNoise(float CurrentTime);
	void EndStun();

	TWeakObjectPtr<APawn> CurrentTarget;
	TWeakObjectPtr<AActor> CurrentNoise;
	TSet<TWeakObjectPtr<AActor>> CompletedNoises;
	TWeakObjectPtr<AActor> LastNotifiedPlayerNoise;
	TSet<TWeakObjectPtr<AActor>> ObservedGems;
	TWeakObjectPtr<AActor> BoundCageActor;
	UPROPERTY(Transient)
	TSubclassOf<AActor> GemPickupClass;
	UPROPERTY(Transient)
	TSubclassOf<AActor> PlayerNoiseClass;
	FDelegateHandle GemSpawnHandle;
	FVector LastKnownLocation = FVector::ZeroVector;
	float LastStimulusTime = 0.0f;
	float NextSenseTime = 0.0f;
	float NextMoveTime = 0.0f;
	float NextPatrolActionTime = 0.0f;
	float NextNoiseTime = 0.0f;
	float NextPlayerNoiseNotificationTime = 0.0f;
	float NextFlankSwitchTime = 0.0f;
	bool bWaitingAtPatrolPoint = false;
	bool bAnyGemCollected = false;
	bool bResumeFullChaseAfterStun = false;
	bool bFlankLeft = false;
	FTimerHandle StunTimerHandle;
};
