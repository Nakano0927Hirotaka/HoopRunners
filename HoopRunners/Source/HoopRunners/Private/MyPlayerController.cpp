#include "MyPlayerController.h"
#include "LobbyMode.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

void AMyPlayerController::JoinHost(const FString& IPAddress)
{
    UE_LOG(LogTemp, Warning, TEXT("JoinHost called! IPAddress: %s"), *IPAddress);
    if (IPAddress.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("JoinHost: IPAddress is EMPTY!"));
        return;
    }
    ClientTravel(IPAddress, TRAVEL_Absolute);
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void AMyPlayerController::UpdatePlayers_Implementation(int32 Current, int32 Max)
{
    UE_LOG(LogTemp, Warning, TEXT("UpdatePlayers_Implementation called: %d/%d"), Current, Max);
    OnPlayerCountUpdated(Current, Max);
}

void AMyPlayerController::ShowGameOver_Implementation()
{
    if (GameOverWidgetClass)
    {
        UUserWidget* Widget = CreateWidget<UUserWidget>(this, GameOverWidgetClass);
        if (Widget)
        {
            Widget->AddToViewport();
            FInputModeUIOnly InputMode;
            SetInputMode(InputMode);
            bShowMouseCursor = true;
            UGameplayStatics::SetGamePaused(GetWorld(), true);
        }
    }
}

void AMyPlayerController::ShowGameClear_Implementation()
{
    if (GameClearWidgetClass)
    {
        UUserWidget* Widget = CreateWidget<UUserWidget>(this, GameClearWidgetClass);
        if (Widget)
        {
            Widget->AddToViewport();
            FInputModeUIOnly InputMode;
            SetInputMode(InputMode);
            bShowMouseCursor = true;
            UGameplayStatics::SetGamePaused(GetWorld(), true);
        }
    }
}

void AMyPlayerController::ShowLobby_Implementation()
{
    if (!IsLocalPlayerController()) return;

    UWidgetLayoutLibrary::RemoveAllWidgets(this);

    if (LobbyWidgetClass)
    {
        UUserWidget* Widget = CreateWidget<UUserWidget>(this, LobbyWidgetClass);
        if (Widget)
        {
            Widget->AddToViewport();
            RequestPlayerCount();
        }
    }
}

void AMyPlayerController::RequestPlayerCount_Implementation()
{
    ALobbyMode* LobbyMode = Cast<ALobbyMode>(GetWorld()->GetAuthGameMode());
    if (LobbyMode)
    {
        UpdatePlayers(LobbyMode->GetCurrentPlayerCount(), LobbyMode->MaxPlayers);
    }
}