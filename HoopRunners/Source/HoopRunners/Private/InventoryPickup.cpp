#include "InventoryPickup.h"

#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

#include "InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

AInventoryPickup::AInventoryPickup()
{
	// 取得物自身は動かさず、メッシュと球形の取得範囲を用意する。
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SetReplicateMovement(true);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		ItemMesh->SetStaticMesh(CubeMesh.Object);
		ItemMesh->SetRelativeScale3D(FVector(0.35f));
	}

	InteractionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionVolume"));
	InteractionVolume->SetupAttachment(ItemMesh);
	InteractionVolume->SetSphereRadius(140.0f);
	InteractionVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionVolume->SetCollisionObjectType(ECC_WorldDynamic);
	InteractionVolume->SetCollisionResponseToAllChannels(ECR_Overlap);
	InteractionVolume->SetGenerateOverlapEvents(true);
}

void AInventoryPickup::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// 既存のPickup Blueprintにも同期設定を適用してからプレイを開始する。
	if (HasAuthority() && GetNetMode() != NM_Client)
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AInventoryPickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AInventoryPickup, ItemDefinition);
	DOREPLIFETIME(AInventoryPickup, PickupMesh);
	DOREPLIFETIME(AInventoryPickup, PickupMaterials);
	DOREPLIFETIME(AInventoryPickup, PickupScale);
	DOREPLIFETIME(AInventoryPickup, PickupInteractionRadius);
}

void AInventoryPickup::OnRep_Appearance()
{
	if (!ItemMesh) return;
	if (PickupMesh) ItemMesh->SetStaticMesh(PickupMesh);
	for (int32 Index = 0; Index < PickupMaterials.Num(); ++Index)
	{
		ItemMesh->SetMaterial(Index, PickupMaterials[Index]);
	}
	SetActorScale3D(PickupScale);
}

void AInventoryPickup::InitializeDroppedItem(const FInventoryStack& Stack)
{
	if (!HasAuthority()) return;
	ItemDefinition = Stack.Item;
	PickupMesh = Stack.Mesh;
	PickupMaterials = Stack.Materials;
	PickupScale = Stack.WorldScale;
	PickupInteractionRadius = Stack.InteractionRadius;
	InteractionVolume->SetSphereRadius(PickupInteractionRadius);
	OnRep_Appearance();
}

bool AInventoryPickup::IsAvailable() const
{
	return !IsActorBeingDestroyed() && !bIsBeingCollected && IsValid(ItemDefinition);
}

bool AInventoryPickup::IsInInteractionRange(const AActor* Collector) const
{
	if (!Collector || Collector->GetWorld() != GetWorld() || !InteractionVolume) return false;
	const FVector Center = InteractionVolume->GetComponentLocation();
	// 球とカプセルの距離を使い、カプセル半高を横方向の取得距離に加算しない。
	if (const UCapsuleComponent* Capsule = Collector->FindComponentByClass<UCapsuleComponent>())
	{
		const float HalfLine = FMath::Max(0.0f, Capsule->GetScaledCapsuleHalfHeight() - Capsule->GetScaledCapsuleRadius());
		const FVector Offset = Capsule->GetUpVector() * HalfLine;
		const FVector Closest = FMath::ClosestPointOnSegment(Center,
			Capsule->GetComponentLocation() - Offset, Capsule->GetComponentLocation() + Offset);
		const float Radius = PickupInteractionRadius * InteractionVolume->GetShapeScale()
			+ Capsule->GetScaledCapsuleRadius();
		return FVector::DistSquared(Center, Closest) <= FMath::Square(Radius);
	}
	return FVector::DistSquared(Center, Collector->GetActorLocation())
		<= FMath::Square(PickupInteractionRadius * InteractionVolume->GetShapeScale());
}

void AInventoryPickup::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		PickupMesh = ItemMesh->GetStaticMesh();
		PickupScale = GetActorScale3D();
		PickupInteractionRadius = InteractionVolume->GetUnscaledSphereRadius();
		PickupMaterials.Reset();
		for (UMaterialInterface* Material : ItemMesh->GetMaterials()) PickupMaterials.Add(Material);
	}
	// 範囲の出入りをインベントリへ通知し、開始時点の重なりも登録する。
	InteractionVolume->OnComponentBeginOverlap.AddDynamic(this, &AInventoryPickup::OnVolumeBeginOverlap);
	InteractionVolume->OnComponentEndOverlap.AddDynamic(this, &AInventoryPickup::OnVolumeEndOverlap);
	TArray<AActor*> InitialOverlaps;
	InteractionVolume->GetOverlappingActors(InitialOverlaps, AActor::StaticClass());
	for (AActor* OverlappingActor : InitialOverlaps)
	{
		if (UInventoryComponent* Inventory = OverlappingActor->FindComponentByClass<UInventoryComponent>())
		{
			Inventory->RegisterNearbyPickup(this);
		}
	}
}

void AInventoryPickup::OnVolumeBeginOverlap(UPrimitiveComponent*, AActor* OtherActor,
	UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	// インベントリを持つアクターが入ったとき、取得候補に加える。
	if (OtherActor)
	{
		if (UInventoryComponent* Inventory = OtherActor->FindComponentByClass<UInventoryComponent>())
		{
			Inventory->RegisterNearbyPickup(this);
		}
	}
}

void AInventoryPickup::OnVolumeEndOverlap(UPrimitiveComponent*, AActor* OtherActor,
	UPrimitiveComponent*, int32)
{
	// 範囲から出たアクターの取得候補から、このアイテムを外す。
	if (OtherActor)
	{
		if (UInventoryComponent* Inventory = OtherActor->FindComponentByClass<UInventoryComponent>())
		{
			Inventory->UnregisterNearbyPickup(this);
		}
	}
}

bool AInventoryPickup::Interact(UInventoryComponent* Inventory)
{
	if (!IsValid(Inventory)) return false;
	// 共有Pickup自体はクライアント所有ではないため、Pawnのコンポーネントへ要求を渡す。
	if (!HasAuthority()) return Inventory->RequestPickup(this);
	if (!IsAvailable() || !Inventory->GetOwner() || !Inventory->GetOwner()->HasAuthority()
		|| !IsInInteractionRange(Inventory->GetOwner()))
	{
		return false;
	}

	// サーバー上で先に確保し、複数プレイヤーからの同時取得を一人だけに限定する。
	bIsBeingCollected = true;
	if (!Inventory->AddPickupItem(this))
	{
		bIsBeingCollected = false;
		return false;
	}

	Destroy();
	return true;
}
