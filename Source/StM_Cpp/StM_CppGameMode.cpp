// Copyright Epic Games, Inc. All Rights Reserved.

#include "StM_CppGameMode.h"
#include "StM_CppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStM_CppGameMode::AStM_CppGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
