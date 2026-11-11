#include "LobbyMode.h"
#include "MyPlayerController.h"
#include "GameFramework/PlayerController.h"

ALobbyMode::ALobbyMode()
{
    PlayerControllerClass = AMyPlayerController::StaticClass();
    // RoomMapではプレイヤーキャラクターを生成しない
    DefaultPawnClass = nullptr;
}

void ALobbyMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    // サーバー側で参加人数を更新
    CurrentPlayerCount = GetNumPlayers();

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("PostLogin: CurrentPlayerCount = %d"),
        CurrentPlayerCount
    );

    // 接続中の全プレイヤーに最新人数を通知
    for (FConstPlayerControllerIterator It =
        GetWorld()->GetPlayerControllerIterator();
        It;
        ++It)
    {
        AMyPlayerController* PC =
            Cast<AMyPlayerController>(It->Get());

        if (PC)
        {
            UE_LOG(
                LogTemp,
                Warning,
                TEXT("Sending player count to %s: %d/%d"),
                *PC->GetName(),
                CurrentPlayerCount,
                MaxPlayers
            );

            PC->UpdatePlayers(CurrentPlayerCount, MaxPlayers);
        }
    }
}

void ALobbyMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);

    CurrentPlayerCount = FMath::Max(0, CurrentPlayerCount - 1);

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Logout: CurrentPlayerCount = %d"),
        CurrentPlayerCount
    );

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
    if (!HasAuthority())
    {
        UE_LOG(LogTemp, Error,
            TEXT("StartGame: No Authority"));
        return;
    }

    // すでに開始処理中なら終了
    if (bIsStartingGame)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("StartGame: Already starting"));
        return;
    }

    UWorld* World = GetWorld();

    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("StartGame: World is NULL"));
        return;
    }

    UE_LOG(LogTemp, Warning,
        TEXT("StartGame: Current map = %s"),
        *World->GetMapName());

    UE_LOG(LogTemp, Warning,
        TEXT("StartGame: Players = %d/%d"),
        CurrentPlayerCount, MaxPlayers);

    UE_LOG(LogTemp, Warning,
        TEXT("StartGame: GameMapName = %s"),
        *GameMapName);

    // 人数確認
    if (CurrentPlayerCount < MaxPlayers)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("StartGame: Not enough players!"));
        return;
    }

    // マップ名確認
    if (GameMapName.IsEmpty())
    {
        UE_LOG(LogTemp, Error,
            TEXT("StartGame: GameMapName is empty"));
        return;
    }


    // ここから開始処理中にする
    bIsStartingGame = true;

    const bool bTravelStarted = World->ServerTravel(GameMapName, true);


    // 遷移開始に失敗した場合は再試行可能にする
    UE_LOG(LogTemp, Warning,
        TEXT("StartGame: ServerTravel returned %d"),
        bTravelStarted);

    if (!bTravelStarted)
    {
        bIsStartingGame = false;

        UE_LOG(LogTemp, Error,
            TEXT("StartGame: Travel failed. Resetting flag."));
    }
    else
    {
        UE_LOG(LogTemp, Warning,
            TEXT("StartGame: Travel request accepted"));
    }
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
