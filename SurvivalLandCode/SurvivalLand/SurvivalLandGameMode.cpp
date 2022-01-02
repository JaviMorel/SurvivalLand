// Copyright Epic Games, Inc. All Rights Reserved.

#include "SurvivalLandGameMode.h"
#include "SurvivalLandCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASurvivalLandGameMode::ASurvivalLandGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
