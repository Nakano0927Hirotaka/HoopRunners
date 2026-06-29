#include "LobbyMode.h"
#include "GameFramework/PlayerController.h"

ALobbyMode::ALobbyMode()
{
}

void ALobbyMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    CurrentPlayerCount++;
}

void ALobbyMode::StartGame()
{
    if (!HasAuthority()) return;

    if (CurrentPlayerCount < MaxPlayers)
    {
        UE_LOG(LogTemp, Warning, TEXT("Not enough players: %d"), CurrentPlayerCount);
        return;
    }

    GetWorld()->ServerTravel(GameMapName + TEXT("?listen"), true);
}

int32 ALobbyMode::GetCurrentPlayerCount() const
{
    return CurrentPlayerCount;
}

void ALobbyMode::NotifyGameOver()
{
    if (!HasAuthority()) return;
}

void ALobbyMode::NotifyGameClear()
{
    if (!HasAuthority()) return;
}