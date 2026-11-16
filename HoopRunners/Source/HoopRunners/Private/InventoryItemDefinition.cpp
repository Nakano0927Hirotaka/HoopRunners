#include "InventoryItemDefinition.h"

#include "Engine/Texture2D.h"
#include "TextureResource.h"

namespace
{
	// EMPアイコンが未設定の既存データ向けに、簡易画像をメモリ上で生成する。
	UTexture2D* CreateEMPFallbackIcon()
	{
		constexpr int32 Size = 64;
		TArray<FColor> Pixels;
		Pixels.SetNumZeroed(Size * Size);

		// 画像の範囲外を書き込まないように画素を設定する。
		auto PutPixel = [&Pixels](int32 X, int32 Y, const FColor& Color)
		{
			if (X >= 0 && X < Size && Y >= 0 && Y < Size)
			{
				Pixels[Y * Size + X] = Color;
			}
		};
		// 四角形と三角形を塗りつぶしてEMPの絵柄を描く。
		auto FillRect = [&PutPixel](int32 MinX, int32 MinY, int32 MaxX, int32 MaxY, const FColor& Color)
		{
			for (int32 Y = MinY; Y <= MaxY; ++Y)
			{
				for (int32 X = MinX; X <= MaxX; ++X)
				{
					PutPixel(X, Y, Color);
				}
			}
		};
		auto FillTriangle = [&PutPixel](FIntPoint A, FIntPoint B, FIntPoint C, const FColor& Color)
		{
			const int32 MinX = FMath::Min3(A.X, B.X, C.X);
			const int32 MaxX = FMath::Max3(A.X, B.X, C.X);
			const int32 MinY = FMath::Min3(A.Y, B.Y, C.Y);
			const int32 MaxY = FMath::Max3(A.Y, B.Y, C.Y);
			auto Edge = [](FIntPoint P1, FIntPoint P2, int32 X, int32 Y)
			{
				return (X - P1.X) * (P2.Y - P1.Y) - (Y - P1.Y) * (P2.X - P1.X);
			};
			for (int32 Y = MinY; Y <= MaxY; ++Y)
			{
				for (int32 X = MinX; X <= MaxX; ++X)
				{
					const int32 E0 = Edge(A, B, X, Y);
					const int32 E1 = Edge(B, C, X, Y);
					const int32 E2 = Edge(C, A, X, Y);
					if ((E0 >= 0 && E1 >= 0 && E2 >= 0) || (E0 <= 0 && E1 <= 0 && E2 <= 0))
					{
						PutPixel(X, Y, Color);
					}
				}
			}
		};

		FillRect(13, 8, 50, 57, FColor(30, 43, 62, 255));
		FillRect(17, 12, 46, 53, FColor(35, 153, 183, 255));
		FillRect(21, 16, 42, 21, FColor(178, 248, 250, 255));
		FillRect(21, 46, 25, 49, FColor(255, 94, 104, 255));
		FillRect(28, 46, 32, 49, FColor(255, 216, 90, 255));
		FillRect(35, 46, 39, 49, FColor(110, 232, 152, 255));
		FillTriangle(FIntPoint(35, 25), FIntPoint(25, 39), FIntPoint(34, 39), FColor(255, 239, 124, 255));
		FillTriangle(FIntPoint(34, 39), FIntPoint(29, 50), FIntPoint(41, 34), FColor(255, 239, 124, 255));
		FillTriangle(FIntPoint(34, 39), FIntPoint(41, 34), FIntPoint(36, 34), FColor(255, 239, 124, 255));

		// 描画した画素を一時テクスチャへ転送し、HUDで使えるようにする。
		UTexture2D* Texture = UTexture2D::CreateTransient(Size, Size, PF_B8G8R8A8);
		if (!Texture)
		{
			return nullptr;
		}
		Texture->SRGB = true;
		auto& Mip = Texture->GetPlatformData()->Mips[0];
		void* TextureData = Mip.BulkData.Lock(LOCK_READ_WRITE);
		FMemory::Memcpy(TextureData, Pixels.GetData(), Pixels.Num() * sizeof(FColor));
		Mip.BulkData.Unlock();
		Texture->UpdateResource();
		return Texture;
	}
}

void UInventoryItemDefinition::PostLoad()
{
	Super::PostLoad();
	// 既存サンプルアイテムをEMPとして扱い、名前・効果・アイコンを補正する。
	if (GetFName() != FName(TEXT("DA_SampleItem")))
	{
		return;
	}

	DisplayName = FText::FromString(TEXT("EMP"));
	UseType = EInventoryItemUseType::EMP;
	// 専用アイコンが利用できない場合は、代替画像を順に読み込む。
	if (!Icon || Icon->GetFName() == FName(TEXT("T_SampleItemIcon")))
	{
		if (UTexture2D* SavedEMPIcon = LoadObject<UTexture2D>(nullptr,
			TEXT("/Game/Inventory/T_EMPIcon.T_EMPIcon")))
		{
			Icon = SavedEMPIcon;
		}
		else if (UTexture2D* FallbackIcon = CreateEMPFallbackIcon())
		{
			Icon = FallbackIcon;
		}
	}
}
