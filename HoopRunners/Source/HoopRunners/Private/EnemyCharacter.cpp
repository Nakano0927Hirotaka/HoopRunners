// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Runtime\AIModule\Classes\AIController.h"
#include "EngineUtils.h"
#include "NavigationSystem.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);

	//AI Perception
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 1500.0f;
	SightConfig->LoseSightRadius = 1800.0f;

	DefaultSightRadius = SightConfig->SightRadius;
	DefaultLoseSightRadius = SightConfig->LoseSightRadius;

	SightConfig->PeripheralVisionAngleDegrees = 60.0f;
	SightConfig->SetMaxAge(5.0f);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	CurrentState = EEnemyState::Patrol;
	CurrentTarget = nullptr;

	bHasPatrolTarget = false;
	bIsStunned = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();

	//接触判定
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(
		this,
		&AEnemyCharacter::OnOverlapBegin
	);

}

void AEnemyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AEnemyCharacter, CurrentState);
	DOREPLIFETIME(AEnemyCharacter, bIsStunned);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AIPerception->OnTargetPerceptionUpdated.AddDynamic(
		this,
		&AEnemyCharacter::OnTargetPerceptionUpdated
	);
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 敵AIの判断はサーバーだけで実行し、移動と状態を複製する。
	if (!HasAuthority())
	{
		return;
	}
	if (bIsStunned)
	{
		return;
	}

	UpdateState();

	switch (CurrentState)
	{
	case EEnemyState::Patrol:
		Patrol();
		break;

	case EEnemyState::Chase:
		Chase();
		break;

	case EEnemyState::FullChase:
		FullChase();
		break;

	default:
		break;
	}

}

//視界更新
void AEnemyCharacter::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor) return;

	//完全追跡中なら無視
	if (CurrentState == EEnemyState::FullChase)
	{
		return;
	}

	if (Stimulus.WasSuccessfullySensed())
	{
		//プレイヤー発見
		CurrentTarget = Actor;
		CurrentState = EEnemyState::Chase;

		LastSeenTime = GetWorld()->GetTimeSeconds();
	}

	else
	{
		if (CurrentTarget == Actor)
		{
			LastSeenTime = GetWorld()->GetTimeSeconds();
		}
	}
}

//巡回
void AEnemyCharacter::Patrol()
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController) return;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSystem) return;

	if (!bHasPatrolTarget)
	{
		FNavLocation RandomLocation;

		if (NavSystem->GetRandomReachablePointInRadius(
			GetActorLocation(),
			2000.0f,
			RandomLocation))
		{
			CurrentPatrolLocation = RandomLocation.Location;
			bHasPatrolTarget = true;

			AIController->MoveToLocation(CurrentPatrolLocation);
		}
	}
	else
	{
		//到着判定
		float DistanceToTarget = FVector::Dist(
			GetActorLocation(),
			CurrentPatrolLocation
		);

		if (DistanceToTarget < 100.0f)
		{
			bHasPatrolTarget = false;
		}
	}
}

//通常追跡
void AEnemyCharacter::Chase()
{
	if (!CurrentTarget) return;

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->MoveToActor(CurrentTarget);
	}
}

//完全追跡
void AEnemyCharacter::FullChase()
{
	ACharacter* ClosestPlayer = nullptr;
	float ClosestDistance = FLT_MAX;

	for (TActorIterator<ACharacter> It(GetWorld()); It; ++It)
	{
		ACharacter* Player = *It;

		if (Player == this) continue;

		float Dist = FVector::Dist(GetActorLocation(), Player->GetActorLocation());

		if (Dist < ClosestDistance)
		{
			ClosestDistance = Dist;
			ClosestPlayer = Player;
		}
	}

	if (ClosestPlayer)
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController)
		{
			AIController->MoveToActor(ClosestPlayer);
		}
	}
}

//状態更新
void AEnemyCharacter::UpdateState()
{
	float GameTime = GetWorld()->GetTimeSeconds();

	// 仮: Gem管理は外部Managerから取得推奨
	int32 GlobalGemCount = 0;

	if (GlobalGemCount >= GemThreshold || GameTime >= FullChaseStartTime)
	{
		CurrentState = EEnemyState::FullChase;
	}

	//追跡継続
	if (CurrentTarget)
	{
		float LostTime = GameTime - LastSeenTime;

		if (LostTime <= LoseSightChaseDuration)
		{

			CurrentState = EEnemyState::Chase;

		}
		else
		{

			CurrentTarget = nullptr;
			CurrentState = EEnemyState::Patrol;
			bHasPatrolTarget = false;

			AAIController* AIController = Cast<AAIController>(GetController());
			if (AIController)
			{
				AIController->StopMovement();
			}
		}
	}
}

//捕獲
void AEnemyCharacter::CapturePlayer(ACharacter* Player)
{
	if (!HasAuthority() || bIsStunned || !Player) return;

	Player->DisableInput(nullptr);
	Player->SetActorLocation(CageLocation);

	CurrentState = EEnemyState::Capture;
}

void AEnemyCharacter::ApplyEMP(float StunDuration)
{
	// EMP処理はサーバーで一度だけ行い、敵の状態と移動停止を同期する。
	if (!HasAuthority() || StunDuration <= 0.0f || !GetWorld())
	{
		return;
	}

	bIsStunned = true;
	CurrentTarget = nullptr;
	CurrentState = EEnemyState::Stunned;
	bHasPatrolTarget = false;

	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->StopMovement();
	}
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();

	GetWorldTimerManager().SetTimer(
		StunTimerHandle,
		this,
		&AEnemyCharacter::EndStun,
		StunDuration,
		false
	);
	ForceNetUpdate();
}

void AEnemyCharacter::EndStun()
{
	if (!HasAuthority())
	{
		return;
	}

	bIsStunned = false;
	CurrentState = EEnemyState::Patrol;
	bHasPatrolTarget = false;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	ForceNetUpdate();
}

//接触判定
void AEnemyCharacter::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	ACharacter* Player = Cast<ACharacter>(OtherActor);

	if (Player && Player != this)
	{
		CapturePlayer(Player);
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

