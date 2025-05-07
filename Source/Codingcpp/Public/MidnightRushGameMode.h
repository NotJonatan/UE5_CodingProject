// Source/Codingcpp/Public/MidnightRushGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MidnightRushGameMode.generated.h"

/** Our custom GameMode: uses ASprintCharacter as the default pawn */
UCLASS()
class CODINGCPP_API AMidnightRushGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMidnightRushGameMode();
};
