#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyMode.generated.h"

UCLASS()
class HOOPRUNNERS_API ALobbyMode : public AGameMode
{
    GENERATED_BODY()

public:
    ALobbyMode();

    virtual void PreLogin(
        const FString& Options,
        const FString& Address,
        const FUniqueNetIdRepl& UniqueId,
        FString& ErrorMessage
    ) override;

    virtual void PostLogin(APlayerController* NewPlayer) override;

    UFUNCTION(BlueprintCallable, Category = "Lobby")
    void StartGame();

    UFUNCTION(BlueprintPure, Category = "Lobby")
    int32 GetCurrentPlayerCount() const;

    UFUNCTION(BlueprintCallable, Category = "Game")
    void NotifyGameOver();

    UFUNCTION(BlueprintCallable, Category = "Game")
    void NotifyGameClear();

    UPROPERTY(EditDefaultsOnly, Category = "Lobby")
    int32 MaxPlayers = 2;

    UPROPERTY(EditDefaultsOnly, Category = "Lobby")
    FString GameMapName = TEXT("/Game/FirstPerson/Lvl_Hoshino");

    // êVãKéQâ¡Çã÷é~Ç∑ÇÈÇ©
    UPROPERTY()
    bool bIsStartingGame = false;

private:
    virtual void Logout(AController* Exiting) override;

    int32 CurrentPlayerCount = 0;
};