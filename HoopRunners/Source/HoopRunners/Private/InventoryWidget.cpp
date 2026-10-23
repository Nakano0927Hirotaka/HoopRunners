#include "InventoryWidget.h"

#include "InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/SizeBox.h"
#include "Components/Widget.h"
#include "Blueprint/WidgetTree.h"
#include "Styling/SlateColor.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// 操作案内を準備し、初期状態の所持品を3枠へ表示する。
	EnsurePickupPrompt();
	RefreshInventory();
}

void UInventoryWidget::SetInventoryComponent(UInventoryComponent* InInventory)
{
	// HUDが参照する所持品を保存し、表示を同期する。
	Inventory = InInventory;
	EnsurePickupPrompt();
	RefreshInventory();
}

void UInventoryWidget::SetActionPrompt(bool bVisible, bool bEMPSelected)
{
	// 選択中のアイテムに合わせて案内文と表示状態を設定する。
	EnsurePickupPrompt();
	if (ActionPromptText)
	{
		ActionPromptText->SetText(FText::FromString(bEMPSelected
			? TEXT("スペースキーでEMP発動")
			: TEXT("スペースキーで取得")));
	}
	if (PickupPromptBackground)
	{
		PickupPromptBackground->SetVisibility(bVisible ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}
}

void UInventoryWidget::EnsurePickupPrompt()
{
	// 既存のWidget階層があればその上に重ね、操作案内を一度だけ作る。
	if (PickupPromptBackground || !WidgetTree || !WidgetTree->RootWidget)
	{
		return;
	}

	UWidget* ExistingRoot = WidgetTree->RootWidget;
	UOverlay* RootOverlay = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), TEXT("InventoryRootOverlay"));
	WidgetTree->RootWidget = RootOverlay;
	RootOverlay->AddChildToOverlay(ExistingRoot);

	ActionPromptText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("ActionPromptText"));
	ActionPromptText->SetText(FText::FromString(TEXT("スペースキーで取得")));
	ActionPromptText->SetJustification(ETextJustify::Center);
	ActionPromptText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	ActionPromptText->SetShadowOffset(FVector2D(1.0f, 1.0f));
	FSlateFontInfo PromptFont = ActionPromptText->GetFont();
	PromptFont.Size = 28;
	ActionPromptText->SetFont(PromptFont);

	PickupPromptBackground = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(), TEXT("PickupPromptBackground"));
	PickupPromptBackground->SetPadding(FMargin(20.0f, 12.0f));
	PickupPromptBackground->SetBrushColor(FLinearColor(0.02f, 0.025f, 0.04f, 0.88f));
	PickupPromptBackground->SetContent(ActionPromptText);
	PickupPromptBackground->SetVisibility(ESlateVisibility::Collapsed);

	if (UOverlaySlot* PromptSlot = RootOverlay->AddChildToOverlay(PickupPromptBackground))
	{
		PromptSlot->SetHorizontalAlignment(HAlign_Center);
		PromptSlot->SetVerticalAlignment(VAlign_Bottom);
		PromptSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 110.0f));
	}
}

void UInventoryWidget::RefreshInventory()
{
	// 3つの枠を作り直し、選択状態、アイコン、個数を最新化する。
	if (!InventorySlots)
	{
		return;
	}

	InventorySlots->ClearChildren();
	const UInventoryComponent* Source = Inventory.Get();
	const TArray<FInventoryStack>* Items = Source ? &Source->GetItems() : nullptr;
	constexpr int32 SlotCount = 3;
	for (int32 SlotIndex = 0; SlotIndex < SlotCount; ++SlotIndex)
	{
		const FInventoryStack* Stack = Items && Items->IsValidIndex(SlotIndex)
			? &(*Items)[SlotIndex]
			: nullptr;
		// データが存在し個数がある枠だけ、アイテム画像を表示する。
		const bool bOccupied = Stack && Stack->Item && Stack->Quantity > 0;
		const bool bSelected = Source && SlotIndex == Source->GetSelectedSlotIndex();

		USizeBox* SlotSize = NewObject<USizeBox>(this);
		SlotSize->SetWidthOverride(100.0f);
		SlotSize->SetHeightOverride(100.0f);

		UBorder* SlotBorder = NewObject<UBorder>(this);
		SlotBorder->SetPadding(FMargin(5.0f));
		SlotBorder->SetBrushColor(bSelected
			? (bOccupied
				? FLinearColor(0.04f, 0.25f, 0.38f, 1.0f)
				: FLinearColor(0.04f, 0.16f, 0.24f, 0.98f))
			: (bOccupied
				? FLinearColor(0.09f, 0.12f, 0.18f, 1.0f)
				: FLinearColor(0.035f, 0.045f, 0.07f, 0.88f)));
		SlotSize->SetContent(SlotBorder);

		UOverlay* SlotContents = NewObject<UOverlay>(this);
		SlotBorder->SetContent(SlotContents);

		// アイテム定義のアイコンを枠の中央に配置する。
		if (bOccupied && Stack->Item->Icon)
		{
			UImage* ItemImage = NewObject<UImage>(this);
			ItemImage->SetBrushFromTexture(Stack->Item->Icon, true);
			SlotContents->AddChildToOverlay(ItemImage);
		}

		UTextBlock* Quantity = NewObject<UTextBlock>(this);
		if (bOccupied && Stack->Quantity > 1)
		{
			Quantity->SetText(FText::Format(
				FText::FromString(TEXT("x{0}")), FText::AsNumber(Stack->Quantity)));
		}
		else
		{
			Quantity->SetText(FText::GetEmpty());
		}
		Quantity->SetColorAndOpacity(FSlateColor(FLinearColor::White));
		FSlateFontInfo QuantityFont = Quantity->GetFont();
		QuantityFont.Size = 14;
		Quantity->SetFont(QuantityFont);
		if (UOverlaySlot* QuantitySlot = SlotContents->AddChildToOverlay(Quantity))
		{
			QuantitySlot->SetHorizontalAlignment(HAlign_Right);
			QuantitySlot->SetVerticalAlignment(VAlign_Bottom);
		}

		if (UHorizontalBoxSlot* BoxSlot = InventorySlots->AddChildToHorizontalBox(SlotSize))
		{
			BoxSlot->SetPadding(FMargin(SlotIndex == 0 ? 0.0f : 6.0f, 0.0f, 0.0f, 0.0f));
		}
	}
}
