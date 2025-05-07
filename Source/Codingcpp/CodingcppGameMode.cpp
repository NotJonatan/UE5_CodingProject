// Copyright Epic Games, Inc. All Rights Reserved.

#include "CodingcppGameMode.h"
#include "CodingcppCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACodingcppGameMode::ACodingcppGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
