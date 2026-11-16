#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyAICharacter.generated.h"

// 敵キャラクターの行動状態を表す列挙型。
UENUM(BlueprintType)
enum class EEnemyAIState : uint8
{
	Patrolling, // NavMesh上を巡回している状態
	Chasing, // 視認したプレイヤーを追跡している状態
	FinalChase, // 終盤に最寄りのプレイヤーを追い続ける状態
	Stunned // EMPなどで一時的に行動できない状態
};

// 視界による追跡、巡回、終盤追跡、EMPスタンを管理する敵キャラクター。
UCLASS(Blueprintable)
class HOOPRUNNERS_API AEnemyAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyAICharacter();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 視界判定に使う距離、角度、更新間隔。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Vision", meta=(ClampMin="100.0"))
	float SightRange = 1800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Vision", meta=(ClampMin="1.0", ClampMax="89.0"))
	float SightHalfAngleDegrees = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Vision", meta=(ClampMin="0.05"))
	float SenseUpdateInterval = 0.15f;

	// 巡回範囲と巡回地点で待つ時間。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Patrol", meta=(ClampMin="100.0"))
	float PatrolRadius = 1200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Patrol", meta=(ClampMin="0.0"))
	float PatrolPauseSeconds = 1.5f;

	// 通常巡回、追跡、終盤追跡それぞれの移動速度。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Movement", meta=(ClampMin="0.0"))
	float PatrolSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Movement", meta=(ClampMin="0.0"))
	float ChaseSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Movement", meta=(ClampMin="0.0"))
	float FinalChaseSpeed = 700.0f;

	// 追跡を諦めるまでの時間と終盤追跡の開始時刻。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Chase", meta=(ClampMin="0.1"))
	float ChaseForgetSeconds = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Final Chase", meta=(ClampMin="0.0"))
	float FinalChaseStartSeconds = 900.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Final Chase", meta=(ClampMin="0.05"))
	float FinalTargetRefreshInterval = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Movement", meta=(ClampMin="0.0"))
	float MoveAcceptanceRadius = 100.0f;

	// 現在のAI状態をBlueprintから読み取る。
	UFUNCTION(BlueprintPure, Category="AI")
	EEnemyAIState GetAIState() const { return CurrentState; }

	// EMPの効果時間だけ敵を停止させる。
	UFUNCTION(BlueprintCallable, Category="AI|Stun")
	void ApplyEMPStun(float DurationSeconds);

	// 状態が切り替わったときにBlueprint側へ通知するイベント。
	UFUNCTION(BlueprintImplementableEvent, Category="AI")
	void OnAIStateChanged(EEnemyAIState NewState);

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	// プレイヤー候補を集め、視界判定や終盤追跡で使う。
	void GatherPlayerPawns(TArray<APawn*>& OutPlayers) const;
	bool FindVisiblePlayer(APawn*& OutPlayer, FVector& OutPlayerLocation) const;
	APawn* FindNearestPlayer() const;
	void UpdateSight(float CurrentTime);
	void UpdateFinalTarget(float CurrentTime);
	void SetAIState(EEnemyAIState NewState);
	void EnterPatrol();
	void EnterChase(APawn* Target, const FVector& TargetLocation, float CurrentTime);
	void EnterFinalChase(float CurrentTime);
	void TickPatrol(float CurrentTime);
	void TickChase(float CurrentTime);
	void ChooseNextPatrolPoint(float CurrentTime);
	bool RequestMoveToLocation(const FVector& Destination, float CurrentTime, bool bForce = false);

	// Blueprintから状態を確認できるよう現在値を公開する。
	UPROPERTY(ReplicatedUsing=OnRep_CurrentState, VisibleAnywhere, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	EEnemyAIState CurrentState = EEnemyAIState::Patrolling;

	// スタン・追跡解除を受信した端末でもBlueprintの表示イベントを実行する。
	UFUNCTION()
	void OnRep_CurrentState();

	// 追跡対象、巡回地点、各種タイマーなどの内部状態。
	TWeakObjectPtr<APawn> CurrentTarget;
	FVector PatrolOrigin = FVector::ZeroVector;
	FVector CurrentDestination = FVector::ZeroVector;
	FVector LastKnownPlayerLocation = FVector::ZeroVector;
	float NextSenseUpdateTime = 0.0f;
	float NextMoveRequestTime = 0.0f;
	float NextPatrolActionTime = 0.0f;
	float NextFinalTargetUpdateTime = 0.0f;
	float LastPlayerSeenTime = 0.0f;
	float NextNavigationWarningTime = 0.0f;
	float EMPStunEndTime = 0.0f;
	bool bHasPatrolDestination = false;
	bool bWaitingAtPatrolPoint = false;
	bool bResumeFinalChaseAfterEMP = false;
};

