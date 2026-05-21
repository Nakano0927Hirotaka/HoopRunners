// Fill out your copyright notice in the Description page of Project Settings.


#include "ConeItemActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"

int32 AConeItemActor::CollectedItemCount = 0;

// Sets default values
AConeItemActor::AConeItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	//メッシュ
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	//Coneメッシュ読み込み
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeMesh(
		TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));

	if (ConeMesh.Succeeded())
	{
		Mesh->SetStaticMesh(ConeMesh.Object);
	}

	//Overlap設定
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	Mesh->SetGenerateOverlapEvents(true);

	//イベントバインド
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AConeItemActor::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AConeItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	// 初期表示
	UpdateItemDisplay();
}

//UI表示更新
void AConeItemActor::UpdateItemDisplay()
{
	if (GEngine)
	{
		FString DisplayText = FString::Printf(TEXT("%d/%d"), CollectedItemCount, MaxItemCount);

		// Key=1 により同じ表示を上書き更新
		GEngine->AddOnScreenDebugMessage(
			1,
			9999.0f,
			FColor::Yellow,
			DisplayText
		);
	}
}

//触れたときの処理
void AConeItemActor::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// 自分自身や無効なActorを除外
	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	//プレイヤー判定（簡易）
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);

	if (PlayerCharacter)
	{

		//カウント加算
		CollectedItemCount++;

		//取得処理（仮）
		UKismetSystemLibrary::PrintString(this, "GET!!!!!!!!!", true, true, FColor::Cyan, 2.0f, TEXT("None"));

		//UI更新
		UpdateItemDisplay();

		//自分を削除
		Destroy();
	}
}

// Called every frame
void AConeItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

