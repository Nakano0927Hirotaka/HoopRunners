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

	//AIímäoÅiçıìGÅjä÷òA
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

	//ê⁄êGîªíË
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

//éãäEçXêV
void AEnemyCharacter::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor) return;

	//äÆëSí«ê’íÜÇ»ÇÁñ≥éã
	if (CurrentState == EEnemyState::FullChase)
	{
		return;
	}

	if (Stimulus.WasSuccessfullySensed())
	{
		//ÉvÉåÉCÉÑÅ[î≠å©
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

//èÑâÒ
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
		//ìûíÖîªíË
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

//í èÌí«ê’
void AEnemyCharacter::Chase()
{
	if (!CurrentTarget) return;

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->MoveToActor(CurrentTarget);
	}
}

//äÆëSí«ê’
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

//èÛë‘çXêV
void AEnemyCharacter::UpdateState()
{
	float GameTime = GetWorld()->GetTimeSeconds();

	// âº: Gemä«óùÇÕäOïîManagerÇ©ÇÁéÊìæêÑèß
	int32 GlobalGemCount = 0;

	if (GlobalGemCount >= GemThreshold || GameTime >= FullChaseStartTime)
	{
		CurrentState = EEnemyState::FullChase;
	}

	//í«ê’åpë±
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

void AEnemyCharacter::CapturePlayer(ACharacter* Player)
{
	if (!Player) return;

	//ëΩèdïﬂälñhé~
	if (CurrentState == EEnemyState::Capture)
	{
		return;
	}

	CurrentState = EEnemyState::Capture;
	CurrentTarget = nullptr;
	bHasPatrolTarget = false;

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->StopMovement();
	}

	const FVector TargetLocation =
		CageActor ? CageActor->GetActorLocation() : CageLocation;

	TWeakObjectPtr<ACharacter> WeakPlayer(Player);
	TWeakObjectPtr<AEnemyCharacter> WeakEnemy(this);

	GetWorldTimerManager().SetTimerForNextTick(
		FTimerDelegate::CreateLambda(
			[WeakPlayer, WeakEnemy, TargetLocation]()
			{
				if (!WeakPlayer.IsValid())
				{
					return;
				}

				ACharacter* P = WeakPlayer.Get();

				//ÉvÉåÉCÉÑÅ[Çí‚é~
				if (UCharacterMovementComponent* MoveComp =
					P->GetCharacterMovement())
				{
					MoveComp->StopMovementImmediately();
				}

				//üBÇ÷ì]ëó
				P->SetActorLocation(
					TargetLocation,
					false,
					nullptr,
					ETeleportType::TeleportPhysics);

				if (UCharacterMovementComponent* MoveComp =
					P->GetCharacterMovement())
				{
					MoveComp->SetMovementMode(MOVE_Walking);
				}

				//EnemyÇÃèÛë‘ÇPatrolÇ÷ñﬂÇ∑
				if (WeakEnemy.IsValid())
				{
					AEnemyCharacter* Enemy = WeakEnemy.Get();

					Enemy->CurrentTarget = nullptr;
					Enemy->bHasPatrolTarget = false;
					Enemy->CurrentState = EEnemyState::Patrol;
				}
			})
	);
}

void AEnemyCharacter::ApplyEMP(float StunDuration)
{
	//ä˘Ç…ÉXÉ^ÉìíÜÇ»ÇÁñ≥éã
	if (bIsStunned)
	{
		return;
	}

	bIsStunned = true;

	//à⁄ìÆí‚é~
	AAIController* AIController = Cast<AAIController>(GetController());

	if (AIController)
	{
		AIController->StopMovement();
	}

	//Chaseâèú
	CurrentTarget = nullptr;
	CurrentState = EEnemyState::Patrol;
	bHasPatrolTarget = false;

	//4ïbå„âèú
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

//ê⁄êGîªíË
void AEnemyCharacter::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin: %s"), OtherActor ? *OtherActor->GetName() : TEXT("null"));

	ACharacter* Player = Cast<ACharacter>(OtherActor);

	if (Player && Player != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("CapturePlayer called"));

		CapturePlayer(Player);
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
