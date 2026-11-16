#include "LobbyMode.h"
#include "MyPlayerController.h"
#include "GameFramework/PlayerController.h"

ALobbyMode::ALobbyMode()
{
    PlayerControllerClass = AMyPlayerController::StaticClass();
}

void ALobbyMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    CurrentPlayerCount++;
    UE_LOG(LogTemp, Warning, TEXT("PostLogin called! CurrentPlayerCount = %d"), CurrentPlayerCount);
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        AMyPlayerController* PC = Cast<AMyPlayerController>(It->Get());
        if (PC)
        {
            PC->UpdatePlayers(CurrentPlayerCount, MaxPlayers);
        }
    }
}

void ALobbyMode::StartGame()
{
    UE_LOG(LogTemp, Warning, TEXT("NetMode = %d"), (int32)GetNetMode());
    UE_LOG(LogTemp, Warning, TEXT("World = %s"), *GetWorld()->GetMapName());

    if (!HasAuthority())
        return;

    UE_LOG(LogTemp, Warning, TEXT("Current=%d Max=%d"), CurrentPlayerCount, MaxPlayers);

    if (CurrentPlayerCount < MaxPlayers)
        return;

    GameMapName = TEXT("/Game/FirstPerson/Lvl_Hoshino");

    bool bResult = GetWorld()->ServerTravel(GameMapName + TEXT("?listen"), true);

    UE_LOG(LogTemp, Warning, TEXT("ServerTravel Result=%d"), bResult);
}

int32 ALobbyMode::GetCurrentPlayerCount() const
{
    return CurrentPlayerCount;
}

void ALobbyMode::NotifyGameOver()
{
    if (!HasAuthority()) return;

    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        AMyPlayerController* PC = Cast<AMyPlayerController>(It->Get());
        if (PC)
        {
            PC->ShowGameOver();
        }
    }
}

void ALobbyMode::NotifyGameClear()
{
    if (!HasAuthority()) return;

    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        AMyPlayerController* PC = Cast<AMyPlayerController>(It->Get());
        if (PC)
        {
            PC->ShowGameClear();
        }
    }
}


void ALobbyMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
    CurrentPlayerCount--;

    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        AMyPlayerController* PC = Cast<AMyPlayerController>(It->Get());
        if (PC)
        {
            PC->UpdatePlayers(CurrentPlayerCount, MaxPlayers);
        }
    }
}