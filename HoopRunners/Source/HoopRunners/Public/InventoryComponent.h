#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItemDefinition.h"
#include "InventoryComponent.generated.h"

class AInventoryPickup;
class APlayerController;
class UInventoryWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryChanged, const TArray<FInventoryStack>&, Items);

// 取得要求が失敗しても、同じ要求を使用操作へ切り替えない。
UENUM()
enum class EInventoryNetworkAction : uint8
{
	Pickup,
	Consume,
	EMP,
	Drop
};

// 所持品をサーバーで管理し、所有プレイヤーだけに内容とHUDを同期する。
UCLASS(ClassGroup=(Gameplay), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class HOOPRUNNERS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UInventoryComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 操作する本人のHUD。未設定の場合は既存WBPを実行時に読み込む。
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|UI")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	// サーバーが確定した所持品を受信したときにも通知する。
	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FInventoryChanged OnInventoryChanged;

	// Eは取得／通常使用、Spaceは取得／EMP使用。
	// クライアントのtrueは要求送信を表す。確定結果はOnInventoryChangedで通知する。
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool TryInteract();
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void CycleSelection(int32 Direction);
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool DropSelectedItem();
	UFUNCTION(BlueprintPure, Category="Inventory")
	int32 GetSelectedSlotIndex() const { return SelectedSlotIndex; }

	// 任意アイテムの追加はサーバーの報酬処理などからだけ呼ぶ。
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Inventory")
	bool AddItem(UInventoryItemDefinition* ItemDefinition);
	bool AddItemWithMesh(UInventoryItemDefinition* ItemDefinition, UStaticMesh* ItemMesh);
	bool AddPickupItem(const AInventoryPickup* Pickup);
	UFUNCTION(BlueprintPure, Category="Inventory")
	const TArray<FInventoryStack>& GetItems() const { return Items; }

	// 既存のPickup.Interactも、所有PawnのRPCを通して処理する。
	bool RequestPickup(AInventoryPickup* Pickup);
	void RegisterNearbyPickup(AInventoryPickup* Pickup);
	void UnregisterNearbyPickup(AInventoryPickup* Pickup);
	bool IsSelectedEMP() const;
	bool UseSelectedEMP();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
	AInventoryPickup* FindNearestPickupInInteractionRange() const;

private:
	// クライアントからアイテム定義を受け取らず、サーバーの所持品とIDを照合する。
	UFUNCTION(Server, Reliable)
	void ServerPerformAction(EInventoryNetworkAction Action, AInventoryPickup* Pickup,
		FGuid InstanceId, int32 ExpectedQuantity);
	bool SubmitAction(EInventoryNetworkAction Action, AInventoryPickup* Pickup = nullptr);
	bool PerformAction(EInventoryNetworkAction Action, AInventoryPickup* Pickup,
		const FGuid& InstanceId, int32 ExpectedQuantity);
	bool InteractLocally(bool bSpaceAction);
	bool ConsumeItemAt(int32 ItemIndex);
	bool DropItemAt(int32 ItemIndex);
	bool AddStack(FInventoryStack Stack);

	UFUNCTION()
	void OnRep_Items();
	void NotifyInventoryChanged();
	APlayerController* GetLocalPlayerController() const;
	void EnsureLocalWidget();
	void RemoveLocalWidget();
	void UpdateActionPrompt();

	UPROPERTY(ReplicatedUsing=OnRep_Items, VisibleAnywhere, BlueprintReadOnly,
		Category="Inventory", meta=(AllowPrivateAccess="true"))
	TArray<FInventoryStack> Items; // 最大3枠。所有接続だけへ同期する
	int32 SelectedSlotIndex = 0; // 選択表示はローカル。操作要求にはアイテムIDを添える
	TSet<TWeakObjectPtr<AInventoryPickup>> NearbyPickups;
	UPROPERTY(Transient)
	TObjectPtr<UInventoryWidget> InventoryWidget;
	TWeakObjectPtr<APlayerController> WidgetPlayerController;
	bool bTriedDefaultWidgetClass = false;

	// 長押し・BlueprintとTickの重複・RPC連打による二重操作を抑える。
	bool bSpaceActionConsumedUntilRelease = false;
	bool bEActionConsumedUntilRelease = false;
	bool bQActionConsumedUntilRelease = false;
	uint64 LastSubmittedActionFrame = MAX_uint64;
	uint64 LastSelectionFrame = MAX_uint64;
	uint64 LastPickupAttemptFrame = MAX_uint64;
	double NextServerActionTime = 0.0;
	double NextPromptUpdateTime = 0.0; // 近くのアイテム検索を毎フレーム実行しない
};
