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

    UPROPERTY(EditDefaultsOnly, Category = "Lobby")
    int32 MaxPlayers = 2;

    UPROPERTY(EditDefaultsOnly, Category = "Lobby")
    FString GameMapName = TEXT("FirstPersonMap");

    virtual void PostLogin(APlayerController* NewPlayer) override;

    UFUNCTION(BlueprintCallable, Category = "Lobby")
    void StartGame();

    UFUNCTION(BlueprintPure, Category = "Lobby")
    int32 GetCurrentPlayerCount() const;

    UFUNCTION(BlueprintCallable, Category = "Game")
    void NotifyGameOver();

    UFUNCTION(BlueprintCallable, Category = "Game")
    void NotifyGameClear();

private:
    int32 CurrentPlayerCount = 0;
};