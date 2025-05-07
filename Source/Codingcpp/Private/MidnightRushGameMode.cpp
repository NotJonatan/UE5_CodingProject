// Source/Codingcpp/Private/MidnightRushGameMode.cpp
#include "MidnightRushGameMode.h"
//#include "Codingcpp.h"                             // causes error if this isn't first library
#include "SprintCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMidnightRushGameMode::AMidnightRushGameMode()
{
    // set our pawn to the sprint character
    DefaultPawnClass = ASprintCharacter::StaticClass();
}
