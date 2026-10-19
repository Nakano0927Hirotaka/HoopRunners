#include "InventoryComponent.h"

#include "InventoryPickup.h"
#include "InventoryWidget.h"
#include "EnemyCharacter.h"
#include "EnemyAICharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/SkeletalMesh.h"
#include "GameFramework/Character.h"
#include "EngineUtils.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "InputCoreTypes.h"
#include "Net/UnrealNetwork.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true); // 所有Pawnの接続を使ってRPCと所持品を送る
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(UInventoryComponent, Items, COND_OwnerOnly);
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	// 既存Blueprintに保存された設定も含め、所持品の同期を有効にする。
	SetIsReplicated(true);
	if (AActor* Owner = GetOwner(); Owner && Owner->HasAuthority())
	{
		Owner->SetReplicates(true);
		Owner->SetReplicateMovement(true);
	}

	// Characterの本体メッシュを全クライアントで表示し、本人視点だけ隠す。
	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		if (USkeletalMeshComponent* BodyMesh = Character->GetMesh())
		{
			// BPに本体メッシュがない場合はプロジェクト内のQuinnと歩行アニメを補う。
			if (!BodyMesh->GetSkeletalMeshAsset())
			{
				static USkeletalMesh* DefaultBodyMesh = LoadObject<USkeletalMesh>(
					nullptr, TEXT("/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple"));
				static UClass* DefaultBodyAnimClass = LoadClass<UAnimInstance>(
					nullptr, TEXT("/Game/Characters/Mannequins/Anims/Unarmed/ABP_Unarmed.ABP_Unarmed_C"));
				if (DefaultBodyMesh)
				{
					BodyMesh->SetSkeletalMeshAsset(DefaultBodyMesh);
				}
				if (DefaultBodyAnimClass)
				{
					BodyMesh->SetAnimInstanceClass(DefaultBodyAnimClass);
				}
			}

			// First Person用の腕はそのままに、本体だけを他プレイヤーへ表示する。
			BodyMesh->SetOnlyOwnerSee(false);
			BodyMesh->SetOwnerNoSee(true);
			BodyMesh->SetVisibility(true, false);
			BodyMesh->SetHiddenInGame(false, false);
		}
	}
	EnsureLocalWidget();
}

void UInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// リスポーン・退出・マップ変更で古いPawnのHUDを残さない。
	RemoveLocalWidget();
	Super::EndPlay(EndPlayReason);
}

APlayerController* UInventoryComponent::GetLocalPlayerController() const
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	APlayerController* Controller = Pawn ? Cast<APlayerController>(Pawn->GetController()) : nullptr;
	return Controller && Controller->IsLocalController() && Controller->GetLocalPlayer() && Controller->GetPawn() == Pawn
		&& GetNetMode() != NM_DedicatedServer ? Controller : nullptr;
}

void UInventoryComponent::RemoveLocalWidget()
{
	if (InventoryWidget)
	{
		InventoryWidget->RemoveFromParent();
		InventoryWidget = nullptr;
	}
	WidgetPlayerController.Reset();
}

void UInventoryComponent::EnsureLocalWidget()
{
	APlayerController* Controller = GetLocalPlayerController();
	if (!Controller || (InventoryWidget && WidgetPlayerController.Get() != Controller)) RemoveLocalWidget();
	if (!Controller || InventoryWidget) return;

	// BeginPlay後にPossessされる参加クライアントでもTickから再試行する。
	if (!InventoryWidgetClass && !bTriedDefaultWidgetClass)
	{
		bTriedDefaultWidgetClass = true;
		InventoryWidgetClass = LoadClass<UInventoryWidget>(nullptr,
			TEXT("/Game/Inventory/WBP_Inventory.WBP_Inventory_C"));
		if (!InventoryWidgetClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("Inventory Widget Class is missing on %s"), *GetNameSafe(GetOwner()));
		}
	}
	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(Controller, InventoryWidgetClass);
		if (InventoryWidget)
		{
			WidgetPlayerController = Controller;
			InventoryWidget->SetInventoryComponent(this);
			if (!InventoryWidget->AddToPlayerScreen(0))
			{
				RemoveLocalWidget(); // Viewportがまだ準備されていなければ次のTickで再生成する
				return;
			}
			UpdateActionPrompt();
		}
	}
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	EnsureLocalWidget();
	APlayerController* Controller = GetLocalPlayerController();
	if (!Controller) return;

	// 取得のSpace押下を離すまで、通信で届いたEMPを自動使用させない。
	if (!Controller->IsInputKeyDown(EKeys::SpaceBar)) bSpaceActionConsumedUntilRelease = false;
	if (!Controller->IsInputKeyDown(EKeys::E)) bEActionConsumedUntilRelease = false;
	if (!Controller->IsInputKeyDown(EKeys::Q)) bQActionConsumedUntilRelease = false;
	if (Controller->WasInputKeyJustPressed(EKeys::MouseScrollUp)) CycleSelection(-1);
	else if (Controller->WasInputKeyJustPressed(EKeys::MouseScrollDown)) CycleSelection(1);
	if (Controller->WasInputKeyJustPressed(EKeys::Q)) DropSelectedItem();
	if (Controller->WasInputKeyJustPressed(EKeys::SpaceBar)) InteractLocally(true);
	else if (Controller->WasInputKeyJustPressed(EKeys::E)) InteractLocally(false);
	if (GetWorld()->GetTimeSeconds() >= NextPromptUpdateTime)
	{
		NextPromptUpdateTime = GetWorld()->GetTimeSeconds() + 0.1;
		UpdateActionPrompt();
	}
}

void UInventoryComponent::UpdateActionPrompt()
{
	if (InventoryWidget)
	{
		const bool bCanPickup = FindNearestPickupInInteractionRange() != nullptr;
		const bool bEMPSelected = IsSelectedEMP();
		// 取得候補がある間は取得案内を優先し、表示と実際の操作を一致させる。
		InventoryWidget->SetActionPrompt(bCanPickup || bEMPSelected, !bCanPickup && bEMPSelected);
	}
}

AInventoryPickup* UInventoryComponent::FindNearestPickupInInteractionRange() const
{
	UWorld* World = GetWorld();
	if (!World || !GetOwner()) return nullptr;
	AInventoryPickup* BestPickup = nullptr;
	float BestDistanceSquared = TNumericLimits<float>::Max();
	for (TActorIterator<AInventoryPickup> It(World); It; ++It)
	{
		AInventoryPickup* Pickup = *It;
		if (!IsValid(Pickup) || !Pickup->IsAvailable() || !Pickup->IsInInteractionRange(GetOwner())) continue;
		const float Distance = FVector::DistSquared(GetOwner()->GetActorLocation(), Pickup->GetActorLocation());
		if (Distance < BestDistanceSquared)
		{
			BestDistanceSquared = Distance;
			BestPickup = Pickup;
		}
	}
	return BestPickup;
}

bool UInventoryComponent::TryInteract()
{
	APlayerController* Controller = GetLocalPlayerController();
	// 既存E/SpaceのBlueprintノードとC++入力を同じ入口にまとめる。
	return InteractLocally(Controller && (Controller->IsInputKeyDown(EKeys::SpaceBar)
		|| Controller->WasInputKeyJustPressed(EKeys::SpaceBar)));
}

bool UInventoryComponent::InteractLocally(bool bSpaceAction)
{
	if (AInventoryPickup* Pickup = FindNearestPickupInInteractionRange()) return RequestPickup(Pickup);
	if (bSpaceAction) return IsSelectedEMP() && UseSelectedEMP();
	return !IsSelectedEMP() && SubmitAction(EInventoryNetworkAction::Consume);
}

bool UInventoryComponent::RequestPickup(AInventoryPickup* Pickup)
{
	return IsValid(Pickup) && SubmitAction(EInventoryNetworkAction::Pickup, Pickup);
}

bool UInventoryComponent::SubmitAction(EInventoryNetworkAction Action, AInventoryPickup* Pickup)
{
	AActor* Owner = GetOwner();
	APlayerController* Controller = GetLocalPlayerController();
	if (!Owner || (!Owner->HasAuthority() && !Controller) || LastSubmittedActionFrame == GFrameCounter) return false;
	// 入力イベントがBlueprintとTickから重複しても、一押し一要求にする。
	if (Controller)
	{
		if (Controller->IsInputKeyDown(EKeys::SpaceBar))
		{
			if (bSpaceActionConsumedUntilRelease) return false;
			bSpaceActionConsumedUntilRelease = true;
		}
		else if (Controller->IsInputKeyDown(EKeys::E))
		{
			if (bEActionConsumedUntilRelease) return false;
			bEActionConsumedUntilRelease = true;
		}
		else if (Controller->IsInputKeyDown(EKeys::Q))
		{
			if (bQActionConsumedUntilRelease) return false;
			bQActionConsumedUntilRelease = true;
		}
	}
	LastSubmittedActionFrame = GFrameCounter;
	FGuid InstanceId;
	int32 ExpectedQuantity = 0;
	if (Action != EInventoryNetworkAction::Pickup)
	{
		if (!Items.IsValidIndex(SelectedSlotIndex)) return false;
		InstanceId = Items[SelectedSlotIndex].InstanceId;
		ExpectedQuantity = Items[SelectedSlotIndex].Quantity;
	}
	if (Owner->HasAuthority()) return PerformAction(Action, Pickup, InstanceId, ExpectedQuantity);
	ServerPerformAction(Action, Pickup, InstanceId, ExpectedQuantity);
	return true;
}

void UInventoryComponent::ServerPerformAction_Implementation(EInventoryNetworkAction Action,
	AInventoryPickup* Pickup, FGuid InstanceId, int32 ExpectedQuantity)
{
	PerformAction(Action, Pickup, InstanceId, ExpectedQuantity);
}

bool UInventoryComponent::PerformAction(EInventoryNetworkAction Action, AInventoryPickup* Pickup,
	const FGuid& InstanceId, int32 ExpectedQuantity)
{
	AActor* Owner = GetOwner();
	UWorld* World = GetWorld();
	if (!Owner || !Owner->HasAuthority() || !World) return false;
	const double Now = World->GetTimeSeconds();
	if (Now < NextServerActionTime) return false;
	NextServerActionTime = Now + 0.1; // ネットワーク経由の過剰な要求を制限する
	if (Action == EInventoryNetworkAction::Pickup)
	{
		// 満杯・取得競合・距離エラーでも、同じ要求から使用へ切り替えない。
		return IsValid(Pickup) && Pickup->GetWorld() == World
			&& Pickup->IsInInteractionRange(Owner) && Pickup->Interact(this);
	}
	// 枠が左詰めされても、押した時点の同じアイテムだけを対象にする。
	const int32 ItemIndex = Items.IndexOfByPredicate([&InstanceId](const FInventoryStack& Stack)
	{
		return Stack.InstanceId == InstanceId;
	});
	if (!InstanceId.IsValid() || !Items.IsValidIndex(ItemIndex) || !Items[ItemIndex].Item
		|| ExpectedQuantity <= 0 || Items[ItemIndex].Quantity != ExpectedQuantity) return false;
	if (Action == EInventoryNetworkAction::Drop) return DropItemAt(ItemIndex);
	if (Action == EInventoryNetworkAction::Consume)
	{
		return Items[ItemIndex].Item->UseType != EInventoryItemUseType::EMP && ConsumeItemAt(ItemIndex);
	}
	if (Action == EInventoryNetworkAction::EMP && Items[ItemIndex].Item->UseType == EInventoryItemUseType::EMP)
	{
		// 効果と消費をサーバーで一度だけ実行する。敵の状態は全クライアントに届く。
		if (!ConsumeItemAt(ItemIndex)) return false;
		for (TActorIterator<AEnemyCharacter> It(World); It; ++It)
		{
			if (IsValid(*It)) It->ApplyEMP(4.0f);
		}
		for (TActorIterator<AEnemyAICharacter> It(World); It; ++It)
		{
			if (IsValid(*It)) It->ApplyEMPStun(4.0f);
		}
		return true;
	}
	return false;
}

bool UInventoryComponent::IsSelectedEMP() const
{
	return Items.IsValidIndex(SelectedSlotIndex) && Items[SelectedSlotIndex].Item
		&& Items[SelectedSlotIndex].Item->UseType == EInventoryItemUseType::EMP
		&& Items[SelectedSlotIndex].Quantity > 0;
}

bool UInventoryComponent::UseSelectedEMP()
{
	return IsSelectedEMP() && SubmitAction(EInventoryNetworkAction::EMP);
}

bool UInventoryComponent::ConsumeItemAt(int32 ItemIndex)
{
	if (!GetOwner() || !GetOwner()->HasAuthority() || !Items.IsValidIndex(ItemIndex)) return false;
	if (--Items[ItemIndex].Quantity <= 0) Items.RemoveAt(ItemIndex);
	NotifyInventoryChanged();
	return true;
}

void UInventoryComponent::CycleSelection(int32 Direction)
{
	if (!GetLocalPlayerController() || Direction == 0 || LastSelectionFrame == GFrameCounter) return;
	LastSelectionFrame = GFrameCounter;
	// 上回転は左、下回転は右へ。選択表示には通信待ちを発生させない。
	SelectedSlotIndex = (SelectedSlotIndex + (Direction > 0 ? 1 : -1) + 3) % 3;
	if (InventoryWidget) InventoryWidget->RefreshInventory();
	UpdateActionPrompt();
}

bool UInventoryComponent::DropSelectedItem()
{
	return SubmitAction(EInventoryNetworkAction::Drop);
}

bool UInventoryComponent::DropItemAt(int32 ItemIndex)
{
	if (!GetOwner() || !GetOwner()->HasAuthority() || !GetWorld() || !Items.IsValidIndex(ItemIndex)) return false;
	const FInventoryStack Stack = Items[ItemIndex];
	AActor* Owner = GetOwner();
	float HalfHeight = 0.0f;
	if (const UCapsuleComponent* Capsule = Owner->FindComponentByClass<UCapsuleComponent>())
	{
		HalfHeight = Capsule->GetScaledCapsuleHalfHeight();
	}
	const FVector Location = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 120.0f
		+ FVector(0.0f, 0.0f, 40.0f - HalfHeight);
	const FTransform Transform(Owner->GetActorRotation(), Location, Stack.WorldScale);
	// 所有者を限定しない共有アイテムとしてサーバーで生成する。
	AInventoryPickup* Dropped = GetWorld()->SpawnActorDeferred<AInventoryPickup>(
		AInventoryPickup::StaticClass(), Transform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (!Dropped) return false;
	Dropped->InitializeDroppedItem(Stack);
	Dropped->FinishSpawning(Transform);
	if (!IsValid(Dropped)) return false;
	return ConsumeItemAt(ItemIndex);
}

bool UInventoryComponent::AddItem(UInventoryItemDefinition* ItemDefinition)
{
	return AddItemWithMesh(ItemDefinition, nullptr);
}

bool UInventoryComponent::AddItemWithMesh(UInventoryItemDefinition* ItemDefinition, UStaticMesh* ItemMesh)
{
	FInventoryStack Stack;
	Stack.Item = ItemDefinition;
	Stack.Mesh = ItemMesh;
	return AddStack(Stack);
}

bool UInventoryComponent::AddPickupItem(const AInventoryPickup* Pickup)
{
	if (!IsValid(Pickup) || !GetOwner() || !GetOwner()->HasAuthority()
		|| LastPickupAttemptFrame == GFrameCounter) return false;
	LastPickupAttemptFrame = GFrameCounter; // 既存BPが重なり候補を順番に呼んでも一つだけ取得する
	FInventoryStack Stack;
	Stack.Item = Pickup->ItemDefinition;
	Stack.WorldScale = Pickup->GetActorScale3D();
	if (Pickup->InteractionVolume) Stack.InteractionRadius = Pickup->InteractionVolume->GetUnscaledSphereRadius();
	if (Pickup->ItemMesh)
	{
		Stack.Mesh = Pickup->ItemMesh->GetStaticMesh();
		for (UMaterialInterface* Material : Pickup->ItemMesh->GetMaterials()) Stack.Materials.Add(Material);
	}
	return AddStack(Stack);
}

bool UInventoryComponent::AddStack(FInventoryStack Stack)
{
	if (!GetOwner() || !GetOwner()->HasAuthority() || !Stack.Item || Items.Num() >= 3) return false;
	Stack.InstanceId = FGuid::NewGuid(); // 同種のアイテム同士も区別する
	Stack.Quantity = 1;
	Items.Add(MoveTemp(Stack));
	NotifyInventoryChanged();
	return true;
}

void UInventoryComponent::OnRep_Items()
{
	NotifyInventoryChanged();
}

void UInventoryComponent::NotifyInventoryChanged()
{
	SelectedSlotIndex = FMath::Clamp(SelectedSlotIndex, 0, 2);
	if (GetOwner() && GetOwner()->HasAuthority()) GetOwner()->ForceNetUpdate();
	OnInventoryChanged.Broadcast(Items);
	if (InventoryWidget) InventoryWidget->RefreshInventory();
	UpdateActionPrompt();
}

void UInventoryComponent::RegisterNearbyPickup(AInventoryPickup* Pickup)
{
	if (IsValid(Pickup)) NearbyPickups.Add(Pickup);
}

void UInventoryComponent::UnregisterNearbyPickup(AInventoryPickup* Pickup)
{
	NearbyPickups.Remove(Pickup);
}
