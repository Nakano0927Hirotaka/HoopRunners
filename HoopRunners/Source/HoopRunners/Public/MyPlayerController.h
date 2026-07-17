#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class HOOPRUNNERS_API AMyPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    // ロビーUIのWidgetクラス
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> LobbyWidgetClass;

    virtual void BeginPlay() override;

    // 指定したIPアドレスのホストへ接続する
    UFUNCTION(BlueprintCallable, Category = "Network")
    void JoinHost(const FString& IPAddress);

    // 自分がホスト（サーバー）かどうか判定する
    UFUNCTION(BlueprintPure, Category = "Network")
    bool IsHost() const { return HasAuthority(); }

    // ロビーの人数をクライアントへ通知する
    UFUNCTION(Client, Reliable)
    void UpdatePlayers(int32 Current, int32 Max);

    // ゲームオーバーUI表示
    UFUNCTION(Client, Reliable, BlueprintCallable)
    void ShowGameOver();

    // ゲームクリアUI表示
    UFUNCTION(Client, Reliable, BlueprintCallable)
    void ShowGameClear();

    // ロビーUIを表示する
    UFUNCTION(Client, Reliable)
    void ShowLobby();

    UFUNCTION(Server, Reliable)
    void RequestPlayerCount();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> GameClearWidgetClass;

    UFUNCTION(BlueprintImplementableEvent, Category = "Lobby")
    void OnPlayerCountUpdated(int32 Current, int32 Max);
};