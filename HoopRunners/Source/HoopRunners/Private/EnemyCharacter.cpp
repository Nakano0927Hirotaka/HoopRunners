// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "NavigationSystem.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	if (!Player) return;

	Player->DisableInput(nullptr);
	Player->SetActorLocation(CageLocation);

	CurrentState = EEnemyState::Capture;
}

void AEnemyCharacter::ApplyEMP(float StunDuration)
{
	//既にスタン中なら無視
	if (bIsStunned)
	{
		return;
	}

	bIsStunned = true;

	//移動停止
	AAIController* AIController = Cast<AAIController>(GetController());

	if (AIController)
	{
		AIController->StopMovement();
	}

	//Chase解除
	CurrentTarget = nullptr;
	CurrentState = EEnemyState::Patrol;
	bHasPatrolTarget = false;

	//4秒後解除
	GetWorldTimerManager().SetTimer(
		StunTimerHandle,
		this,
		&AEnemyCharacter::EndStun,
		StunDuration,
		false
	);
}

void AEnemyCharacter::EndStun()
{
	bIsStunned = false;
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