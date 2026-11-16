#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InventoryItemDefinition.generated.h"

class UStaticMesh;
class UMaterialInterface;

// アイテムを使ったときに実行する効果の種類。
UENUM(BlueprintType)
enum class EInventoryItemUseType : uint8
{
	None, // 直接使用効果を持たないアイテム
	EMP // 全敵をスタンさせるEMP
};

// 表示名、アイコン、使用効果をまとめたアイテム定義。
UCLASS(BlueprintType)
class HOOPRUNNERS_API UInventoryItemDefinition : public UDataAsset
{
	GENERATED_BODY()

public:
	// 保存済みのアイテム定義を読み込んだ後、必要な既定値を補う。
	virtual void PostLoad() override;

	// UIに表示する名前。
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	FText DisplayName = FText::FromString(TEXT("アイテム"));

	// インベントリ枠に表示する画像。
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	TObjectPtr<UTexture2D> Icon;

	// 使用時に適用する効果。
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item|Use")
	EInventoryItemUseType UseType = EInventoryItemUseType::None;
};

// インベントリ内の一枠に格納するアイテムと個数。
USTRUCT(BlueprintType)
struct FInventoryStack
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	TObjectPtr<UInventoryItemDefinition> Item; // この枠に格納しているアイテム

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	TObjectPtr<UStaticMesh> Mesh; // ドロップ時に元の見た目を復元するメッシュ

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	TArray<TObjectPtr<UMaterialInterface>> Materials; // 他クライアントにも復元する保存済みマテリアル

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	FVector WorldScale = FVector(0.35f); // 取得した時点の表示サイズ

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	float InteractionRadius = 140.0f; // ドロップ後も同じ取得範囲を復元する

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	FGuid InstanceId; // 遅延した操作で別のアイテムを消費しないための識別子

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	int32 Quantity = 0; // この枠にある個数
};
