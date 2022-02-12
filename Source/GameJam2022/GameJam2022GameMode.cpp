// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameJam2022GameMode.h"
#include "GameJam2022PlayerController.h"
#include "GameJam2022Character.h"
#include "UObject/ConstructorHelpers.h"

AGameJam2022GameMode::AGameJam2022GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGameJam2022PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}