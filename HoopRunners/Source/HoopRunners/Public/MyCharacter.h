#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "InputMappingContext.h"
#include "InputAction.h"

#include "MyCharacter.generated.h"

UCLASS()
class HOOPRUNNERS_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyCharacter();

protected:
    virtual void BeginPlay() override;

    virtual void SetupPlayerInputComponent(
        class UInputComponent* PlayerInputComponent) override;

    void Move(const FInputActionValue& Value);

    void Look(const FInputActionValue& Value);

    void StartRun();

    void StopRun();

protected:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* RunAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed = 250.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float RunSpeed = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bIsRunning = false;
};
USTRUCT(BlueprintType)
struct FNoiseData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius = 500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration = 60.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Interval = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bOneShot = false;
};