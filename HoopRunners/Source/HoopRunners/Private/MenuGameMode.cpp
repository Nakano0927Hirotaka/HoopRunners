// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"

#include "MyPlayerController.h"

AMenuGameMode::AMenuGameMode()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
}