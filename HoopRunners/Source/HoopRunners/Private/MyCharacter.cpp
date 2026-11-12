#include "MyCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Engine/LocalPlayer.h"

AMyCharacter::AMyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

    if (APlayerController* PlayerController =
        Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void AMyCharacter::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput =
        Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInput->BindAction(
            MoveAction,
            ETriggerEvent::Triggered,
            this,
            &AMyCharacter::Move);

        EnhancedInput->BindAction(
            RunAction,
            ETriggerEvent::Started,
            this,
            &AMyCharacter::StartRun);

        EnhancedInput->BindAction(
            RunAction,
            ETriggerEvent::Completed,
            this,
            &AMyCharacter::StopRun);

        EnhancedInput->BindAction(
            LookAction,
            ETriggerEvent::Triggered,
            this,
            &AMyCharacter::Look);

        EnhancedInput->BindAction(
            JumpAction,
            ETriggerEvent::Started,
            this,
            &ACharacter::Jump);

        EnhancedInput->BindAction(
            JumpAction,
            ETriggerEvent::Completed,
            this,
            &ACharacter::StopJumping);
    }
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    AddMovementInput(GetActorForwardVector(), MovementVector.Y);

    AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AMyCharacter::StartRun()
{
    bIsRunning = true;
    GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AMyCharacter::StopRun()
{
    bIsRunning = false;
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    // ç∂âE
    AddControllerYawInput(LookAxisVector.X);

    // è„â∫
    AddControllerPitchInput(LookAxisVector.Y);
}