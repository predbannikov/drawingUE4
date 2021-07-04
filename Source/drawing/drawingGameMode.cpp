// Copyright Epic Games, Inc. All Rights Reserved.

#include "drawingGameMode.h"
#include "drawingHUD.h"
#include "drawingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AdrawingGameMode::AdrawingGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AdrawingHUD::StaticClass();
}
