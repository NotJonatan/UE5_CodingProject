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

/*  ── THIS FUNCTION MUST BE OUTSIDE ANY OTHER FUNCTION ─────────────── */
void AMidnightRushGameMode::AddUploaded(int32 Amount)
{
	NumUploaded += Amount;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,                              // key
			2.f,                             // time
			FColor::Silver,                  // colour
			FString::Printf(TEXT("Uploaded %d / %d"), NumUploaded, DrivesGoal)
		);
	}

	if (NumUploaded >= DrivesGoal)
	{
		OnGoalReached.Broadcast();
	}
}
