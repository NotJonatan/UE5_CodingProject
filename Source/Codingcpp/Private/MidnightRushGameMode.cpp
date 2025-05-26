// Source/Codingcpp/Private/MidnightRushGameMode.cpp
#include "MidnightRushGameMode.h"
//#include "Codingcpp.h"                             // causes error if this isn't first library
//#include "SprintCharacter.h"

void AMidnightRushGameMode::AddUploaded(int32 Amount)
{
    NumUploaded += Amount;
    OnUploadedProgress.Broadcast(NumUploaded, DrivesGoal);

    if (NumUploaded >= DrivesGoal)
    {
        OnGoalReached.Broadcast();
    }
}