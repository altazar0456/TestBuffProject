// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestBuffProjectGameMode.h"
#include "TestBuffProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestBuffProjectGameMode::ATestBuffProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
