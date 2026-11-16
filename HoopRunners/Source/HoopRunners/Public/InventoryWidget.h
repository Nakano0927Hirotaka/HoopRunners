#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemDefinition.h"
#include "InventoryWidget.generated.h"

class UInventoryComponent;
class UHorizontalBox;
class UBorder;
class UTextBlock;

// 3枠のインベントリと取得／EMP使用の操作案内を表示するHUD。
UCLASS(Blueprintable)
class HOOPRUNNERS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 所持品コンポーネントを設定し、表示内容を更新する。
	void SetInventoryComponent(UInventoryComponent* InInventory);
	// 選択状態、アイコン、個数を枠へ反映する。
	void RefreshInventory();
	// 取得範囲や選択アイテムに応じて操作案内を切り替える。
	void SetActionPrompt(bool bVisible, bool bEMPSelected);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UHorizontalBox> InventorySlots; // 横並びの3枠を配置するWidget

private:
	// 操作案内の背景と文字Widgetを必要に応じて作成する。
	void EnsurePickupPrompt();

	TWeakObjectPtr<UInventoryComponent> Inventory;
	UPROPERTY(Transient)
	TObjectPtr<UBorder> PickupPromptBackground;
	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> ActionPromptText;
};
