#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItemDefinition.h"
#include "InventoryPickup.generated.h"

class UInventoryComponent;
class UInventoryItemDefinition;
class USphereComponent;
class UStaticMeshComponent;

// プレイヤーが近づいて操作するとインベントリへ入るアイテムアクター。
UCLASS(Blueprintable)
class HOOPRUNNERS_API AInventoryPickup : public AActor
{
	GENERATED_BODY()

public:
	AInventoryPickup();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// 同じ距離判定をサーバーの取得許可とローカル案内の両方で使う。
	bool IsInInteractionRange(const AActor* Collector) const;
	bool IsAvailable() const;
	void InitializeDroppedItem(const FInventoryStack& Stack);

	// ワールドに表示するアイテムのメッシュ。
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pickup")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	// プレイヤーが取得可能になる範囲。
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pickup")
	TObjectPtr<USphereComponent> InteractionVolume;

	// この取得物が表すアイテムの定義。
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Pickup")
	TObjectPtr<UInventoryItemDefinition> ItemDefinition;

	// 取得処理を行い、成功した場合はこのアクターを破棄する。
	UFUNCTION(BlueprintCallable, Category="Pickup")
	bool Interact(UInventoryComponent* Inventory);

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

private:
	// 初期配置・ドロップ・途中参加のいずれでも、サーバー側の外観を復元する。
	UFUNCTION()
	void OnRep_Appearance();
	UPROPERTY(ReplicatedUsing=OnRep_Appearance)
	TObjectPtr<UStaticMesh> PickupMesh;
	UPROPERTY(ReplicatedUsing=OnRep_Appearance)
	TArray<TObjectPtr<UMaterialInterface>> PickupMaterials;
	UPROPERTY(ReplicatedUsing=OnRep_Appearance)
	FVector PickupScale = FVector(0.35f);
	UPROPERTY(Replicated)
	float PickupInteractionRadius = 140.0f; // ドロップ後も同じ取得範囲を用いる

	// プレイヤーが範囲に入った／出たとき、所持品側の候補一覧を更新する。
	UFUNCTION()
	void OnVolumeBeginOverlap(UPrimitiveComponent* Overlapped, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnVolumeEndOverlap(UPrimitiveComponent* Overlapped, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	bool bIsBeingCollected = false; // 重なった複数入力による二重取得を防ぐ
};
