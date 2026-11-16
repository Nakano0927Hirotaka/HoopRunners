#include "EnemyAICharacter.h"
#include "Net/UnrealNetwork.h"

#include "AIController.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMesh.h"
#include "EngineUtils.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "UObject/ConstructorHelpers.h"

namespace
{
	// プレイヤー判定と移動命令を調整するためのタグ・間隔・しきい値。
	const FName PlayerTag(TEXT("Player"));
	constexpr float MoveRequestInterval = 0.35f;
	constexpr float FinalTargetMoveThreshold = 100.0f;
}

AEnemyAICharacter::AEnemyAICharacter()
{
	// AIControllerを自動で割り当て、サンプル用のメッシュとアニメーションを設定する。
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMesh(
		TEXT("/Game/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple"));
	if (DefaultMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(DefaultMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> DefaultAnimation(
		TEXT("/Game/Characters/Mannequins/Anims/Unarmed/ABP_Unarmed"));
	if (DefaultAnimation.Class)
	{
		GetMesh()->SetAnimInstanceClass(DefaultAnimation.Class);
	}
}

void AEnemyAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (HasAuthority() && GetNetMode() != NM_Client)
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AEnemyAICharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AEnemyAICharacter, CurrentState);
}

void AEnemyAICharacter::OnRep_CurrentState()
{
	// AI判断はサーバーだけで行い、クライアントは表示用の状態を反映する。
	OnAIStateChanged(CurrentState);
}

void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	if (!HasAuthority()) return;
	// 配置位置を巡回中心として記録し、AI制御と巡回を開始する。
	PatrolOrigin = GetActorLocation();
	if (!GetController())
	{
		SpawnDefaultController();
	}

	const float CurrentTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	NextSenseUpdateTime = CurrentTime;
	EnterPatrol();
}

void AEnemyAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!HasAuthority()) return; // クライアントで独自の巡回・追跡・スタン解除を実行しない
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	const float CurrentTime = World->GetTimeSeconds();
	// スタン中は効果時間が切れるまでAIの行動更新を止める。
	if (CurrentState == EEnemyAIState::Stunned)
	{
		if (CurrentTime < EMPStunEndTime)
		{
			return;
		}

		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		if (bResumeFinalChaseAfterEMP)
		{
			bResumeFinalChaseAfterEMP = false;
			EnterFinalChase(CurrentTime);
		}
		else
		{
			EnterPatrol();
		}
	}

	// 設定時刻を過ぎたら、視界による追跡から終盤の継続追跡へ移る。
	if (CurrentState != EEnemyAIState::FinalChase
		&& CurrentTime >= FMath::Max(FinalChaseStartSeconds, 0.0f))
	{
		EnterFinalChase(CurrentTime);
	}

	if (CurrentState == EEnemyAIState::FinalChase)
	{
		if (CurrentTime >= NextFinalTargetUpdateTime)
		{
			UpdateFinalTarget(CurrentTime);
		}
	}
	else if (CurrentTime >= NextSenseUpdateTime)
	{
		NextSenseUpdateTime = CurrentTime + FMath::Max(SenseUpdateInterval, 0.05f);
		UpdateSight(CurrentTime);
	}

	switch (CurrentState)
	{
	case EEnemyAIState::Patrolling:
		TickPatrol(CurrentTime);
		break;
	case EEnemyAIState::Chasing:
		TickChase(CurrentTime);
		break;
	case EEnemyAIState::FinalChase:
	case EEnemyAIState::Stunned:
		break;
	default:
		break;
	}
}

void AEnemyAICharacter::ApplyEMPStun(float DurationSeconds)
{
	UWorld* World = GetWorld();
	if (!HasAuthority() || !World || !FMath::IsFinite(DurationSeconds) || DurationSeconds <= 0.0f)
	{
		return;
	}

	// EMP前の終盤追跡状態だけ記録し、解除後に再開できるようにする。
	if (CurrentState != EEnemyAIState::Stunned)
	{
		bResumeFinalChaseAfterEMP = CurrentState == EEnemyAIState::FinalChase;
	}
	EMPStunEndTime = FMath::Max(EMPStunEndTime, World->GetTimeSeconds() + DurationSeconds);
	CurrentTarget.Reset();
	bHasPatrolDestination = false;
	bWaitingAtPatrolPoint = false;
	// 移動命令と速度を即座に止め、スタン状態へ切り替える。
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->StopMovement();
	}
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
	SetAIState(EEnemyAIState::Stunned);
}

void AEnemyAICharacter::GatherPlayerPawns(TArray<APawn*>& OutPlayers) const
{
	// PlayerController配下のPawnとPlayerタグ付きPawnを重複なく集める。
	OutPlayers.Reset();
	const UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		const APlayerController* PlayerController = It->Get();
		if (APawn* PlayerPawn = PlayerController ? PlayerController->GetPawn() : nullptr)
		{
			OutPlayers.AddUnique(PlayerPawn);
		}
	}

	for (TActorIterator<APawn> It(World); It; ++It)
	{
		if (It->ActorHasTag(PlayerTag))
		{
			OutPlayers.AddUnique(*It);
		}
	}
}

bool AEnemyAICharacter::FindVisiblePlayer(APawn*& OutPlayer, FVector& OutPlayerLocation) const
{
	// 距離、視野角、遮蔽物を調べ、最も近い可視プレイヤーを返す。
	OutPlayer = nullptr;
	const UWorld* World = GetWorld();
	if (!World)
	{
		return false;
	}

	FVector EyeLocation;
	FRotator EyeRotation;
	GetActorEyesViewPoint(EyeLocation, EyeRotation);
	const float MinimumDot = FMath::Cos(FMath::DegreesToRadians(SightHalfAngleDegrees));
	float BestDistanceSquared = TNumericLimits<float>::Max();
	TArray<APawn*> Players;
	GatherPlayerPawns(Players);

	for (APawn* PlayerPawn : Players)
	{
		if (!IsValid(PlayerPawn) || PlayerPawn == this)
		{
			continue;
		}

		const FVector TargetLocation = PlayerPawn->GetPawnViewLocation();
		const FVector ToTarget = TargetLocation - EyeLocation;
		const float DistanceSquared = ToTarget.SizeSquared();
		if (DistanceSquared > FMath::Square(SightRange) || DistanceSquared <= SMALL_NUMBER
			|| FVector::DotProduct(GetActorForwardVector(), ToTarget.GetSafeNormal()) < MinimumDot)
		{
			continue;
		}

		FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(EnemySightTrace), false, this);
		FHitResult Hit;
		const bool bHit = World->LineTraceSingleByChannel(
			Hit, EyeLocation, TargetLocation, ECC_Visibility, QueryParams);
		if (bHit && Hit.GetActor() != PlayerPawn)
		{
			continue;
		}

		if (DistanceSquared < BestDistanceSquared)
		{
			BestDistanceSquared = DistanceSquared;
			OutPlayer = PlayerPawn;
			OutPlayerLocation = TargetLocation;
		}
	}

	return OutPlayer != nullptr;
}

APawn* AEnemyAICharacter::FindNearestPlayer() const
{
	// 終盤追跡で使用する、敵から最も近いプレイヤーを探す。
	TArray<APawn*> Players;
	GatherPlayerPawns(Players);

	APawn* NearestPlayer = nullptr;
	float BestDistanceSquared = TNumericLimits<float>::Max();
	for (APawn* PlayerPawn : Players)
	{
		if (!IsValid(PlayerPawn) || PlayerPawn == this)
		{
			continue;
		}

		const float DistanceSquared = FVector::DistSquared(GetActorLocation(), PlayerPawn->GetActorLocation());
		if (DistanceSquared < BestDistanceSquared)
		{
			BestDistanceSquared = DistanceSquared;
			NearestPlayer = PlayerPawn;
		}
	}
	return NearestPlayer;
}

void AEnemyAICharacter::UpdateSight(float CurrentTime)
{
	// プレイヤーを視認したら追跡し、見失った時間が続けば巡回へ戻る。
	APawn* VisiblePlayer = nullptr;
	FVector VisibleLocation;
	if (FindVisiblePlayer(VisiblePlayer, VisibleLocation))
	{
		if (CurrentState != EEnemyAIState::Chasing || CurrentTarget.Get() != VisiblePlayer)
		{
			EnterChase(VisiblePlayer, VisibleLocation, CurrentTime);
		}
		else
		{
			LastKnownPlayerLocation = VisibleLocation;
			LastPlayerSeenTime = CurrentTime;
			RequestMoveToLocation(LastKnownPlayerLocation, CurrentTime);
		}
		return;
	}

	if (CurrentState == EEnemyAIState::Chasing && CurrentTime - LastPlayerSeenTime >= ChaseForgetSeconds)
	{
		EnterPatrol();
	}
}

void AEnemyAICharacter::UpdateFinalTarget(float CurrentTime)
{
	// 一定間隔で最寄りプレイヤーを確認し、移動先を更新する。
	NextFinalTargetUpdateTime = CurrentTime + FMath::Max(FinalTargetRefreshInterval, 0.05f);
	APawn* NearestPlayer = FindNearestPlayer();
	if (!NearestPlayer)
	{
		if (CurrentTarget.IsValid())
		{
			CurrentTarget.Reset();
			if (AAIController* AIController = Cast<AAIController>(GetController()))
			{
				AIController->StopMovement();
			}
		}
		return;
	}

	const FVector NewTargetLocation = NearestPlayer->GetActorLocation();
	const bool bTargetChanged = CurrentTarget.Get() != NearestPlayer;
	const bool bTargetMoved = FVector::DistSquared(LastKnownPlayerLocation, NewTargetLocation)
		>= FMath::Square(FinalTargetMoveThreshold);
	CurrentTarget = NearestPlayer;
	LastKnownPlayerLocation = NewTargetLocation;
	RequestMoveToLocation(NewTargetLocation, CurrentTime, bTargetChanged || bTargetMoved);
}

void AEnemyAICharacter::SetAIState(EEnemyAIState NewState)
{
	if (CurrentState == EEnemyAIState::FinalChase
		&& NewState != EEnemyAIState::FinalChase
		&& NewState != EEnemyAIState::Stunned)
	{
		return;
	}
	// 状態が実際に変化したときだけ保存してBlueprintへ通知する。
	if (CurrentState == NewState)
	{
		return;
	}

	CurrentState = NewState;
	ForceNetUpdate();
	OnAIStateChanged(NewState);
}

void AEnemyAICharacter::EnterPatrol()
{
	// 追跡対象を解除し、巡回速度に戻して次の巡回地点を選ぶ。
	if (CurrentState == EEnemyAIState::FinalChase)
	{
		return;
	}

	CurrentTarget.Reset();
	bHasPatrolDestination = false;
	bWaitingAtPatrolPoint = false;
	SetAIState(EEnemyAIState::Patrolling);
	GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->StopMovement();
	}
	NextPatrolActionTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	ChooseNextPatrolPoint(NextPatrolActionTime);
}

void AEnemyAICharacter::EnterChase(APawn* Target, const FVector& TargetLocation, float CurrentTime)
{
	// 視認した対象と位置を記録し、追跡速度で移動を始める。
	if (CurrentState == EEnemyAIState::FinalChase || !IsValid(Target))
	{
		return;
	}

	const bool bNewTarget = CurrentState != EEnemyAIState::Chasing || CurrentTarget.Get() != Target;
	CurrentTarget = Target;
	LastKnownPlayerLocation = TargetLocation;
	LastPlayerSeenTime = CurrentTime;
	bHasPatrolDestination = false;
	bWaitingAtPatrolPoint = false;
	SetAIState(EEnemyAIState::Chasing);
	GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
	RequestMoveToLocation(TargetLocation, CurrentTime, bNewTarget);
}

void AEnemyAICharacter::EnterFinalChase(float CurrentTime)
{
	// 終盤追跡へ切り替え、最寄りプレイヤーを継続して追う。
	if (CurrentState == EEnemyAIState::FinalChase)
	{
		return;
	}

	bHasPatrolDestination = false;
	bWaitingAtPatrolPoint = false;
	SetAIState(EEnemyAIState::FinalChase);
	GetCharacterMovement()->MaxWalkSpeed = FinalChaseSpeed;
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->StopMovement();
	}
	NextFinalTargetUpdateTime = 0.0f;
	UpdateFinalTarget(CurrentTime);
}

void AEnemyAICharacter::TickPatrol(float CurrentTime)
{
	// 巡回地点への到着と待機時間を処理し、次の地点を選ぶ。
	if (bWaitingAtPatrolPoint)
	{
		if (CurrentTime >= NextPatrolActionTime)
		{
			bWaitingAtPatrolPoint = false;
			bHasPatrolDestination = false;
			ChooseNextPatrolPoint(CurrentTime);
		}
		return;
	}

	if (!bHasPatrolDestination)
	{
		if (CurrentTime >= NextPatrolActionTime)
		{
			ChooseNextPatrolPoint(CurrentTime);
		}
		return;
	}

	if (FVector::DistSquared(GetActorLocation(), CurrentDestination) <= FMath::Square(MoveAcceptanceRadius))
	{
		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			AIController->StopMovement();
		}
		bWaitingAtPatrolPoint = true;
		NextPatrolActionTime = CurrentTime + PatrolPauseSeconds;
		return;
	}

	// 移動が失敗・中断された場合は、別の到達可能地点を選び巡回を継続する。
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		if (AIController->GetMoveStatus() == EPathFollowingStatus::Idle
			&& CurrentTime >= NextMoveRequestTime)
		{
			bHasPatrolDestination = false;
			NextPatrolActionTime = CurrentTime + 0.25f;
		}
	}
}

void AEnemyAICharacter::TickChase(float CurrentTime)
{
	// 視界更新の間も直近のプレイヤー位置への移動を維持する。
	if (CurrentTime - LastPlayerSeenTime >= ChaseForgetSeconds)
	{
		EnterPatrol();
		return;
	}
	RequestMoveToLocation(LastKnownPlayerLocation, CurrentTime);
}

void AEnemyAICharacter::ChooseNextPatrolPoint(float CurrentTime)
{
	// NavMesh上から巡回中心の近くにある到達可能地点を選択する。
	UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation ProjectedPatrolOrigin;
	const bool bHasProjectedOrigin = NavigationSystem && NavigationSystem->ProjectPointToNavigation(
		PatrolOrigin, ProjectedPatrolOrigin, FVector(500.0f, 500.0f, 1000.0f));
	FNavLocation PatrolLocation;
	if (!bHasProjectedOrigin || !NavigationSystem->GetRandomReachablePointInRadius(
		ProjectedPatrolOrigin.Location, PatrolRadius, PatrolLocation))
	{
		bHasPatrolDestination = false;
		NextPatrolActionTime = CurrentTime + 1.0f;
		if (CurrentTime >= NextNavigationWarningTime)
		{
			UE_LOG(LogTemp, Warning,
				TEXT("%s: Patrol could not find a reachable NavMesh point. Check that a NavMeshBoundsVolume covers the floor (press P to show the NavMesh)."),
				*GetName());
			NextNavigationWarningTime = CurrentTime + 5.0f;
		}
		return;
	}

	PatrolOrigin = ProjectedPatrolOrigin.Location;
	CurrentDestination = PatrolLocation.Location;
	bHasPatrolDestination = true;
	bWaitingAtPatrolPoint = false;
	if (!RequestMoveToLocation(CurrentDestination, CurrentTime, true))
	{
		bHasPatrolDestination = false;
		NextPatrolActionTime = CurrentTime + 0.5f;
	}
}

bool AEnemyAICharacter::RequestMoveToLocation(const FVector& Destination, float CurrentTime, bool bForce)
{
	// AIControllerへ移動要求を送り、失敗時はNavMesh不足などを警告する。
	if (!bForce && CurrentTime < NextMoveRequestTime)
	{
		return true;
	}
	NextMoveRequestTime = CurrentTime + MoveRequestInterval;
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		const EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(
			Destination, MoveAcceptanceRadius);
		if (Result != EPathFollowingRequestResult::Failed)
		{
			return true;
		}

		if (CurrentTime >= NextNavigationWarningTime)
		{
			UE_LOG(LogTemp, Warning,
				TEXT("%s: MoveTo request failed. Check that the enemy and destination are connected by NavMesh."),
				*GetName());
			NextNavigationWarningTime = CurrentTime + 5.0f;
		}
		return false;
	}

	if (CurrentTime >= NextNavigationWarningTime)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: No AIController is assigned; the enemy cannot move."), *GetName());
		NextNavigationWarningTime = CurrentTime + 5.0f;
	}
	return false;
}
