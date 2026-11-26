#include "EnemyCharacter.h"

#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"
#include "Net/UnrealNetwork.h"
#include "NoiseActor.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "UObject/UnrealType.h"
#if WITH_EDITOR
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#endif

namespace
{
	const FName PlayerTag(TEXT("Player"));
	const FName CapturedTag(TEXT("Captured"));
	const FName GemCollectedTag(TEXT("AnyGemCollected"));
	const FName GemCountProperty(TEXT("Jewly"));
	constexpr float MoveRequestInterval = 0.35f;
	constexpr float PatrolArrivalDistance = 100.0f;
	constexpr float FlankSideDistance = 400.0f;
	constexpr float FlankBehindDistance = 300.0f;
	constexpr float PlayerNoiseNotificationCooldown = 3.0f;
}

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();

	// Keep the inherited components used by BP_EnemyCharacter.
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 5000.0f;
	SightConfig->LoseSightRadius = 5000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 30.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlapBegin);
}

void AEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (!HasAuthority())
	{
		// Suppress inherited Blueprint tick and overlap gameplay on simulated clients.
		SetActorTickEnabled(false);
		GetCapsuleComponent()->SetGenerateOverlapEvents(false);
		return;
	}
	SetReplicates(true);
	SetReplicateMovement(true);
}

void AEnemyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AEnemyCharacter, CurrentState);
}

void AEnemyCharacter::OnRep_CurrentState()
{
	OnEnemyStateChanged(CurrentState);
}

void AEnemyCharacter::SetState(EEnemyState NewState)
{
	if (!HasAuthority() || CurrentState == NewState) return;
	if (NewState == EEnemyState::Chase || NewState == EEnemyState::FullChase)
	{
		if (CurrentState != EEnemyState::Chase && CurrentState != EEnemyState::FullChase)
		{
			NextNoiseTime = GetWorld()->GetTimeSeconds();
		}
	}
	CurrentState = NewState;
	ForceNetUpdate();
	OnEnemyStateChanged(NewState);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AIPerception->SetComponentTickEnabled(false);
	if (!HasAuthority()) return;

	if (!GetController()) SpawnDefaultController();
	GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;
	GemPickupClass = LoadClass<AActor>(nullptr, TEXT("/Game/Jewelry/Jewly.Jewly_C"));
	PlayerNoiseClass = LoadClass<AActor>(nullptr,
		TEXT("/Game/FirstPerson/Blueprints/BP_NoiseActor.BP_NoiseActor_C"));
	if (GemPickupClass)
	{
		for (TActorIterator<AActor> It(GetWorld()); It; ++It) RegisterGemActor(*It);
		GemSpawnHandle = GetWorld()->AddOnActorSpawnedHandler(
			FOnActorSpawned::FDelegate::CreateUObject(this, &AEnemyCharacter::OnActorSpawned));
	}
	NextSenseTime = GetWorld()->GetTimeSeconds();
	UpdateGemCollection();
	EnterPatrol();
}

void AEnemyCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		if (GemSpawnHandle.IsValid()) World->RemoveOnActorSpawnedHandler(GemSpawnHandle);
	}
	for (const TWeakObjectPtr<AActor>& Gem : ObservedGems)
	{
		if (Gem.IsValid()) Gem->OnActorBeginOverlap.RemoveDynamic(this, &AEnemyCharacter::OnGemOverlap);
	}
	if (BoundCageActor.IsValid())
	{
		BoundCageActor->OnActorEndOverlap.RemoveDynamic(this, &AEnemyCharacter::OnCageEndOverlap);
	}
	Super::EndPlay(EndPlayReason);
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!HasAuthority() || !GetWorld()) return;

	const float CurrentTime = GetWorld()->GetTimeSeconds();
	UpdateGemCollection();
	if (CurrentState == EEnemyState::Stun) return;

	if (!bAnyGemCollected && CurrentTime >= NoGemFullChaseDelaySeconds
		&& CurrentState != EEnemyState::FullChase)
	{
		StartFullChase();
	}

	if (CurrentTime >= NextSenseTime)
	{
		NextSenseTime = CurrentTime + FMath::Max(SenseInterval, 0.05f);
		if (CurrentState == EEnemyState::FullChase)
		{
			if (AActor* Noise = FindBestAudibleNoise())
			{
				NotifyPlayerNoiseDetected(Noise, CurrentTime);
			}
		}
		else
		{
			UpdateSenses(CurrentTime);
		}
	}

	TryCaptureNearbyPlayer();

	switch (CurrentState)
	{
	case EEnemyState::Patrol:
		TickPatrol(CurrentTime, DeltaTime);
		break;
	case EEnemyState::Chase:
		TickChase(CurrentTime, DeltaTime);
		break;
	case EEnemyState::FullChase:
		TickFullChase(CurrentTime);
		break;
	case EEnemyState::Stun:
		break;
	}

	if (CurrentState == EEnemyState::Chase || CurrentState == EEnemyState::FullChase)
	{
		EmitChaseNoise(CurrentTime);
	}
}

void AEnemyCharacter::GatherPlayers(TArray<APawn*>& OutPlayers) const
{
	OutPlayers.Reset();
	const UWorld* World = GetWorld();
	if (!World) return;

	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		if (const APlayerController* LocalController = It->Get())
		{
			if (APawn* Pawn = LocalController->GetPawn()) OutPlayers.AddUnique(Pawn);
		}
	}
	for (TActorIterator<APawn> It(World); It; ++It)
	{
		if (It->ActorHasTag(PlayerTag)) OutPlayers.AddUnique(*It);
	}
}

bool AEnemyCharacter::IsAvailablePlayer(const APawn* Player) const
{
	return IsValid(Player) && Player != this && !Player->ActorHasTag(CapturedTag);
}

APawn* AEnemyCharacter::FindNearestVisiblePlayer(FVector& OutLocation) const
{
	UWorld* World = GetWorld();
	if (!World) return nullptr;

	FVector EyeLocation;
	FRotator EyeRotation;
	GetActorEyesViewPoint(EyeLocation, EyeRotation);
	const float MinDot = FMath::Cos(FMath::DegreesToRadians(SightHalfAngleDegrees));
	float BestDistanceSquared = TNumericLimits<float>::Max();
	APawn* BestPlayer = nullptr;
	TArray<APawn*> Players;
	GatherPlayers(Players);

	for (APawn* Player : Players)
	{
		if (!IsAvailablePlayer(Player)) continue;
		const FVector TargetLocation = Player->GetPawnViewLocation();
		const FVector ToTarget = TargetLocation - EyeLocation;
		const float DistanceSquared = ToTarget.SizeSquared();
		if (DistanceSquared <= SMALL_NUMBER || DistanceSquared > FMath::Square(SightRange)
			|| FVector::DotProduct(GetActorForwardVector(), ToTarget.GetSafeNormal()) < MinDot)
		{
			continue;
		}

		FCollisionQueryParams Params(SCENE_QUERY_STAT(MainEnemySight), false, this);
		FHitResult Hit;
		if (World->LineTraceSingleByChannel(Hit, EyeLocation, TargetLocation, ECC_Visibility, Params)
			&& Hit.GetActor() != Player)
		{
			continue;
		}
		if (DistanceSquared < BestDistanceSquared)
		{
			BestDistanceSquared = DistanceSquared;
			BestPlayer = Player;
			OutLocation = TargetLocation;
		}
	}
	return BestPlayer;
}

APawn* AEnemyCharacter::FindNearestPlayer() const
{
	TArray<APawn*> Players;
	GatherPlayers(Players);
	APawn* BestPlayer = nullptr;
	float BestDistanceSquared = TNumericLimits<float>::Max();
	for (APawn* Player : Players)
	{
		if (!IsAvailablePlayer(Player)) continue;
		const float DistanceSquared = FVector::DistSquared(GetActorLocation(), Player->GetActorLocation());
		if (DistanceSquared < BestDistanceSquared)
		{
			BestDistanceSquared = DistanceSquared;
			BestPlayer = Player;
		}
	}
	return BestPlayer;
}

AActor* AEnemyCharacter::FindBestAudibleNoise() const
{
	UWorld* World = GetWorld();
	if (!World) return nullptr;

	AActor* BestNoise = nullptr;
	float BestRemainingTime = 0.0f;
	auto ConsiderNoise = [this, &BestNoise, &BestRemainingTime](AActor* Noise,
		float Radius, float RemainingTime)
	{
		if (!IsValid(Noise) || (Noise->GetOwner() && Noise->GetOwner()->IsA<AEnemyCharacter>())
			|| CompletedNoises.Contains(TWeakObjectPtr<AActor>(Noise)) || RemainingTime <= 0.0f
			|| Radius <= 0.0f || FVector::DistSquared(GetActorLocation(), Noise->GetActorLocation())
				> FMath::Square(Radius))
		{
			return;
		}
		if (RemainingTime > BestRemainingTime)
		{
			BestRemainingTime = RemainingTime;
			BestNoise = Noise;
		}
	};

	for (TActorIterator<ANoiseActor> It(World); It; ++It)
	{
		ANoiseActor* Noise = *It;
		if (IsValid(Noise) && !Noise->bFromMainEnemy)
		{
			ConsiderNoise(Noise, Noise->Radius, Noise->GetRemainingDuration());
		}
	}

	// Player Blueprints spawn BP_NoiseActor, which inherits AActor rather than ANoiseActor.
	if (PlayerNoiseClass)
	{
		const FNumericProperty* RadiusProperty = FindFProperty<FNumericProperty>(
			PlayerNoiseClass.Get(), TEXT("Radius"));
		const FNumericProperty* DurationProperty = FindFProperty<FNumericProperty>(
			PlayerNoiseClass.Get(), TEXT("Duration"));
		for (TActorIterator<AActor> It(World, PlayerNoiseClass.Get()); It; ++It)
		{
			AActor* Noise = *It;
			float Radius = RadiusProperty ? static_cast<float>(RadiusProperty->GetFloatingPointPropertyValue(
				RadiusProperty->ContainerPtrToValuePtr<void>(Noise))) : 0.0f;
			if (const USphereComponent* Range = Noise->FindComponentByClass<USphereComponent>())
			{
				Radius = Range->GetScaledSphereRadius();
			}
			const float Duration = DurationProperty ? static_cast<float>(
				DurationProperty->GetFloatingPointPropertyValue(
					DurationProperty->ContainerPtrToValuePtr<void>(Noise))) : 0.0f;
			ConsiderNoise(Noise, Radius, Duration - Noise->GetGameTimeSinceCreation());
		}
	}
	return BestNoise;
}

bool AEnemyCharacter::IsPlayerNoise(const AActor* Noise) const
{
	if (!IsValid(Noise)) return false;
	if (PlayerNoiseClass && Noise->IsA(PlayerNoiseClass.Get())) return true;
	const APawn* SourcePawn = Noise->GetInstigator();
	if (!SourcePawn) SourcePawn = Cast<APawn>(Noise->GetOwner());
	return SourcePawn && (SourcePawn->IsPlayerControlled() || SourcePawn->ActorHasTag(PlayerTag));
}

void AEnemyCharacter::NotifyPlayerNoiseDetected(AActor* Noise, float CurrentTime)
{
	if (!IsPlayerNoise(Noise) || LastNotifiedPlayerNoise.Get() == Noise
		|| CurrentTime < NextPlayerNoiseNotificationTime)
	{
		return;
	}
	LastNotifiedPlayerNoise = Noise;
	NextPlayerNoiseNotificationTime = CurrentTime + PlayerNoiseNotificationCooldown;
	UE_LOG(LogTemp, Display, TEXT("%s detected player noise from %s at %s"),
		*GetName(), *Noise->GetName(), *Noise->GetActorLocation().ToCompactString());
#if WITH_EDITOR
	if (GIsEditor && !IsRunningCommandlet())
	{
		FNotificationInfo Info(FText::FromString(FString::Printf(
			TEXT("%s: プレイヤーの騒音を検知"), *GetName())));
		Info.ExpireDuration = 3.0f;
		Info.bUseThrobber = false;
		Info.bUseSuccessFailIcons = false;
		Info.bUseLargeFont = false;
		FSlateNotificationManager::Get().AddNotification(Info);
	}
#endif
}

void AEnemyCharacter::NotifyGemCollected()
{
	if (!HasAuthority() || !GetWorld()) return;
	if (AGameStateBase* GameState = GetWorld()->GetGameState())
	{
		GameState->Tags.AddUnique(GemCollectedTag);
	}
	for (TActorIterator<AEnemyCharacter> It(GetWorld()); It; ++It)
	{
		It->bAnyGemCollected = true;
	}
}

void AEnemyCharacter::RegisterGemActor(AActor* Actor)
{
	if (!IsValid(Actor) || !GemPickupClass || !Actor->IsA(GemPickupClass)) return;
	Actor->OnActorBeginOverlap.AddUniqueDynamic(this, &AEnemyCharacter::OnGemOverlap);
	ObservedGems.Add(Actor);
}

void AEnemyCharacter::OnActorSpawned(AActor* Actor)
{
	RegisterGemActor(Actor);
}

void AEnemyCharacter::OnGemOverlap(AActor* GemActor, AActor* OtherActor)
{
	if (!HasAuthority() || !IsValid(GemActor)) return;
	APawn* Candidate = Cast<APawn>(OtherActor);
	if (!Candidate) return;
	TArray<APawn*> Players;
	GatherPlayers(Players);
	if (Players.Contains(Candidate)) NotifyGemCollected();
}

void AEnemyCharacter::OnCageEndOverlap(AActor*, AActor* OtherActor)
{
	APawn* Player = Cast<APawn>(OtherActor);
	if (HasAuthority() && IsValid(Player) && Player->ActorHasTag(CapturedTag))
	{
		ReleaseCapturedPlayer(Player);
	}
}

void AEnemyCharacter::UpdateGemCollection()
{
	if (bAnyGemCollected || !GetWorld()) return;
	if (const AGameStateBase* GameState = GetWorld()->GetGameState())
	{
		if (GameState->ActorHasTag(GemCollectedTag))
		{
			bAnyGemCollected = true;
			return;
		}
	}

	TArray<APawn*> Players;
	GatherPlayers(Players);
	for (const APawn* Player : Players)
	{
		const APlayerState* GemPlayerState = Player ? Player->GetPlayerState() : nullptr;
		const FIntProperty* GemProperty = GemPlayerState
			? FindFProperty<FIntProperty>(GemPlayerState->GetClass(), GemCountProperty) : nullptr;
		if (GemProperty && GemProperty->GetPropertyValue_InContainer(GemPlayerState) > 0)
		{
			NotifyGemCollected();
			return;
		}
	}
}

void AEnemyCharacter::UpdateSenses(float CurrentTime)
{
	for (auto It = CompletedNoises.CreateIterator(); It; ++It)
	{
		if (!It->IsValid()) It.RemoveCurrent();
	}
	AActor* AudibleNoise = FindBestAudibleNoise();
	if (AudibleNoise) NotifyPlayerNoiseDetected(AudibleNoise, CurrentTime);
	FVector VisibleLocation = FVector::ZeroVector;
	if (APawn* VisiblePlayer = FindNearestVisiblePlayer(VisibleLocation))
	{
		const bool bNewTarget = CurrentState != EEnemyState::Chase
			|| CurrentTarget.Get() != VisiblePlayer;
		CurrentTarget = VisiblePlayer;
		CurrentNoise.Reset();
		LastKnownLocation = VisibleLocation;
		LastStimulusTime = CurrentTime;
		bHasPatrolTarget = false;
		bWaitingAtPatrolPoint = false;
		SetState(EEnemyState::Chase);
		GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
		RequestMove(LastKnownLocation, CurrentTime, bNewTarget);
		return;
	}

	CurrentTarget.Reset();
	if (AActor* Noise = AudibleNoise)
	{
		const bool bNewNoise = CurrentState != EEnemyState::Chase || CurrentNoise.Get() != Noise;
		CurrentNoise = Noise;
		LastKnownLocation = Noise->GetActorLocation();
		LastStimulusTime = CurrentTime;
		bHasPatrolTarget = false;
		bWaitingAtPatrolPoint = false;
		SetState(EEnemyState::Chase);
		GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
		RequestMove(LastKnownLocation, CurrentTime, bNewNoise);
		return;
	}

	if (CurrentState == EEnemyState::Chase
		&& CurrentTime - LastStimulusTime >= LoseSightChaseDuration)
	{
		EnterPatrol();
	}
}

void AEnemyCharacter::EnterPatrol()
{
	if (!HasAuthority()) return;
	CurrentTarget.Reset();
	CurrentNoise.Reset();
	bHasPatrolTarget = false;
	bWaitingAtPatrolPoint = false;
	SetState(EEnemyState::Patrol);
	GetCharacterMovement()->MaxWalkSpeed = PatrolSpeed;
	if (AAIController* LocalController = Cast<AAIController>(GetController())) LocalController->StopMovement();
	NextPatrolActionTime = GetWorld()->GetTimeSeconds();
}

void AEnemyCharacter::ChoosePatrolPoint(float CurrentTime)
{
	UNavigationSystemV1* Navigation = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation Point;
	if (!Navigation || !Navigation->GetRandomReachablePointInRadius(
		GetActorLocation(), PatrolRadius, Point))
	{
		NextPatrolActionTime = CurrentTime + 1.0f;
		return;
	}
	CurrentPatrolLocation = Point.Location;
	bHasPatrolTarget = RequestMove(CurrentPatrolLocation, CurrentTime, true);
	if (!bHasPatrolTarget) NextPatrolActionTime = CurrentTime + 0.5f;
}

void AEnemyCharacter::TickPatrol(float CurrentTime, float DeltaTime)
{
	if (bWaitingAtPatrolPoint)
	{
		AddActorWorldRotation(FRotator(0.0f, 90.0f * DeltaTime, 0.0f));
		if (CurrentTime >= NextPatrolActionTime)
		{
			bWaitingAtPatrolPoint = false;
			ChoosePatrolPoint(CurrentTime);
		}
		return;
	}
	if (!bHasPatrolTarget)
	{
		if (CurrentTime >= NextPatrolActionTime) ChoosePatrolPoint(CurrentTime);
		return;
	}
	if (FVector::DistSquared(GetActorLocation(), CurrentPatrolLocation)
		<= FMath::Square(PatrolArrivalDistance))
	{
		if (AAIController* LocalController = Cast<AAIController>(GetController())) LocalController->StopMovement();
		bHasPatrolTarget = false;
		bWaitingAtPatrolPoint = true;
		NextPatrolActionTime = CurrentTime + FMath::FRandRange(
			FMath::Min(PatrolWaitMin, PatrolWaitMax), FMath::Max(PatrolWaitMin, PatrolWaitMax));
		return;
	}
	if (AAIController* LocalController = Cast<AAIController>(GetController()))
	{
		if (LocalController->GetMoveStatus() == EPathFollowingStatus::Idle && CurrentTime >= NextMoveTime)
		{
			bHasPatrolTarget = false;
			NextPatrolActionTime = CurrentTime + 0.25f;
		}
	}
}

void AEnemyCharacter::TickChase(float CurrentTime, float DeltaTime)
{
	if (CurrentTime - LastStimulusTime >= LoseSightChaseDuration)
	{
		EnterPatrol();
		return;
	}
	if (CurrentNoise.IsValid()
		&& FVector::DistSquared(GetActorLocation(), CurrentNoise->GetActorLocation())
			<= FMath::Square(NoiseArrivalDistance))
	{
		CompletedNoises.Add(CurrentNoise);
		CurrentNoise.Reset();
		if (AAIController* LocalController = Cast<AAIController>(GetController())) LocalController->StopMovement();
	}
	if (!CurrentTarget.IsValid() && !CurrentNoise.IsValid()
		&& FVector::DistSquared(GetActorLocation(), LastKnownLocation)
			<= FMath::Square(NoiseArrivalDistance))
	{
		AddActorWorldRotation(FRotator(0.0f, SearchTurnDegreesPerSecond * DeltaTime, 0.0f));
		return;
	}
	RequestMove(LastKnownLocation, CurrentTime);
}

bool AEnemyCharacter::RequestMove(const FVector& Destination, float CurrentTime, bool bForce)
{
	if (!bForce && CurrentTime < NextMoveTime) return true;
	NextMoveTime = CurrentTime + MoveRequestInterval;
	AAIController* LocalController = Cast<AAIController>(GetController());
	return LocalController && LocalController->MoveToLocation(Destination, PatrolArrivalDistance)
		!= EPathFollowingRequestResult::Failed;
}

void AEnemyCharacter::StartFullChase()
{
	if (!HasAuthority() || !GetWorld()) return;
	if (CurrentState == EEnemyState::Stun)
	{
		bResumeFullChaseAfterStun = true;
		return;
	}
	if (CurrentState == EEnemyState::FullChase) return;
	CurrentNoise.Reset();
	CurrentTarget.Reset();
	bHasPatrolTarget = false;
	bWaitingAtPatrolPoint = false;
	SetState(EEnemyState::FullChase);
	GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
	if (AAIController* LocalController = Cast<AAIController>(GetController())) LocalController->StopMovement();
	NextFlankSwitchTime = 0.0f;
	TickFullChase(GetWorld()->GetTimeSeconds());
}

void AEnemyCharacter::TickFullChase(float CurrentTime)
{
	APawn* Player = FindNearestPlayer();
	if (!Player)
	{
		CurrentTarget.Reset();
		if (AAIController* LocalController = Cast<AAIController>(GetController())) LocalController->StopMovement();
		return;
	}
	const bool bNewTarget = CurrentTarget.Get() != Player;
	CurrentTarget = Player;
	const FVector TargetLocation = Player->GetActorLocation();
	FVector Destination = TargetLocation;

	// When a wall blocks the direct view, alternate reachable side approaches.
	FCollisionQueryParams Params(SCENE_QUERY_STAT(MainEnemyFlank), false, this);
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), Player->GetPawnViewLocation(),
		ECC_Visibility, Params) && Hit.GetActor() != Player)
	{
		if (CurrentTime >= NextFlankSwitchTime)
		{
			bFlankLeft = !bFlankLeft;
			NextFlankSwitchTime = CurrentTime + 3.0f;
		}
		const FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal2D();
		const FVector Side = FVector::CrossProduct(FVector::UpVector, Direction)
			* (bFlankLeft ? -1.0f : 1.0f);
		const FVector Candidate = TargetLocation - Direction * FlankBehindDistance
			+ Side * FlankSideDistance;
		if (UNavigationSystemV1* Navigation = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
		{
			FNavLocation FlankPoint;
			if (Navigation->ProjectPointToNavigation(Candidate, FlankPoint, FVector(300.0f)))
			{
				Destination = FlankPoint.Location;
			}
		}
	}
	RequestMove(Destination, CurrentTime, bNewTarget);
}

void AEnemyCharacter::TryCaptureNearbyPlayer()
{
	TArray<APawn*> Players;
	GatherPlayers(Players);
	APawn* Nearest = nullptr;
	float BestDistanceSquared = FMath::Square(CaptureDistance);
	for (APawn* Player : Players)
	{
		if (!IsAvailablePlayer(Player)) continue;
		const float DistanceSquared = FVector::DistSquared(GetActorLocation(), Player->GetActorLocation());
		if (DistanceSquared <= BestDistanceSquared)
		{
			BestDistanceSquared = DistanceSquared;
			Nearest = Player;
		}
	}
	if (Nearest) CapturePlayer(Nearest);
}

void AEnemyCharacter::CapturePlayer(APawn* Player)
{
	if (!HasAuthority() || CurrentState == EEnemyState::Stun || !IsAvailablePlayer(Player)) return;

	AActor* DestinationActor = CageActor.Get();
	if (!DestinationActor)
	{
		if (UClass* CageClass = LoadClass<AActor>(nullptr,
			TEXT("/Game/FirstPerson/Blueprints/BP_Cage.BP_Cage_C")))
		{
			for (TActorIterator<AActor> It(GetWorld()); It; ++It)
			{
				if (It->IsA(CageClass))
				{
					DestinationActor = *It;
					break;
				}
			}
		}
	}
	FVector Destination = CageLocation;
	if (DestinationActor)
	{
		if (BoundCageActor.Get() != DestinationActor)
		{
			if (BoundCageActor.IsValid())
			{
				BoundCageActor->OnActorEndOverlap.RemoveDynamic(this, &AEnemyCharacter::OnCageEndOverlap);
			}
			DestinationActor->OnActorEndOverlap.AddUniqueDynamic(this, &AEnemyCharacter::OnCageEndOverlap);
			BoundCageActor = DestinationActor;
		}
		Destination = DestinationActor->GetActorLocation();
		TArray<USceneComponent*> Components;
		DestinationActor->GetComponents<USceneComponent>(Components);
		for (USceneComponent* Component : Components)
		{
			if (Component && Component->GetFName() == FName(TEXT("CagePoint")))
			{
				Destination = Component->GetComponentLocation();
				break;
			}
		}
	}
	else if (CageLocation.IsNearlyZero())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: capture needs a CageActor, BP_Cage, or CageLocation."),
			*GetName());
		return;
	}

	Player->Tags.AddUnique(CapturedTag);
	if (AAIController* LocalController = Cast<AAIController>(GetController())) LocalController->StopMovement();
	if (ACharacter* Character = Cast<ACharacter>(Player))
	{
		Character->GetCharacterMovement()->StopMovementImmediately();
	}
	Player->SetActorLocation(Destination, false, nullptr, ETeleportType::TeleportPhysics);
	CurrentTarget.Reset();
	CurrentNoise.Reset();
	if (CurrentState != EEnemyState::FullChase) EnterPatrol();
}

void AEnemyCharacter::ReleaseCapturedPlayer(APawn* Player)
{
	if (HasAuthority() && IsValid(Player)) Player->Tags.Remove(CapturedTag);
}

void AEnemyCharacter::ApplyEMP(float StunDuration)
{
	if (!HasAuthority() || !GetWorld() || !FMath::IsFinite(StunDuration)) return;
	const float EffectiveDuration = FMath::Max(5.0f, StunDuration);
	if (CurrentState != EEnemyState::Stun)
	{
		bResumeFullChaseAfterStun = CurrentState == EEnemyState::FullChase;
	}
	CurrentTarget.Reset();
	CurrentNoise.Reset();
	bHasPatrolTarget = false;
	bWaitingAtPatrolPoint = false;
	if (AAIController* LocalController = Cast<AAIController>(GetController())) LocalController->StopMovement();
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
	SetState(EEnemyState::Stun);
	GetWorldTimerManager().SetTimer(StunTimerHandle, this, &AEnemyCharacter::EndStun,
		EffectiveDuration, false);
}

void AEnemyCharacter::EndStun()
{
	if (!HasAuthority()) return;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	if (bResumeFullChaseAfterStun
		|| (!bAnyGemCollected && GetWorld()->GetTimeSeconds() >= NoGemFullChaseDelaySeconds))
	{
		bResumeFullChaseAfterStun = false;
		StartFullChase();
	}
	else
	{
		EnterPatrol();
	}
}

void AEnemyCharacter::EmitChaseNoise(float CurrentTime)
{
	if (CurrentTime < NextNoiseTime) return;
	NextNoiseTime = CurrentTime + FMath::Max(EmittedNoiseInterval, 0.05f);
	if (EmittedNoiseRadius <= 0.0f || EmittedNoiseDuration <= 0.0f) return;

	const FTransform SpawnTransform(GetActorRotation(), GetActorLocation());
	ANoiseActor* Pulse = GetWorld()->SpawnActorDeferred<ANoiseActor>(
		ANoiseActor::StaticClass(), SpawnTransform, this, nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (!Pulse) return;
	Pulse->Radius = EmittedNoiseRadius;
	Pulse->Duration = EmittedNoiseDuration;
	Pulse->bFromMainEnemy = true;
	Pulse->bDrawDebug = false;
	Pulse->FinishSpawning(SpawnTransform);
}

void AEnemyCharacter::OnOverlapBegin(UPrimitiveComponent*, AActor* OtherActor,
	UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	APawn* Player = Cast<APawn>(OtherActor);
	if (!HasAuthority() || CurrentState == EEnemyState::Stun || !IsAvailablePlayer(Player)) return;
	TArray<APawn*> Players;
	GatherPlayers(Players);
	if (Players.Contains(Player)
		&& FVector::DistSquared(GetActorLocation(), Player->GetActorLocation())
			<= FMath::Square(CaptureDistance))
	{
		CapturePlayer(Player);
	}
}

AEnemyCharacter* AEnemyCharacter::SpawnAdditionalMainEnemy(
	UObject* WorldContextObject, TSubclassOf<AEnemyCharacter> EnemyClass,
	const FTransform& SpawnTransform)
{
	UWorld* World = WorldContextObject ? WorldContextObject->GetWorld() : nullptr;
	if (!World || World->GetNetMode() == NM_Client) return nullptr;
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	UClass* SpawnClass = EnemyClass.Get();
	if (!SpawnClass)
	{
		SpawnClass = LoadClass<AEnemyCharacter>(nullptr,
			TEXT("/Game/Koguchi/BP_EnemyCharacter.BP_EnemyCharacter_C"));
	}
	if (!SpawnClass) SpawnClass = StaticClass();
	return World->SpawnActor<AEnemyCharacter>(SpawnClass, SpawnTransform, Params);
}
