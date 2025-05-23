// Source/Codingcpp/Public/MidnightRushGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
//#include "SprintCharacter.h"
#include "MidnightRushGameMode.generated.h"

/** Broadcast when the player has uploaded enough drives to win. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGoalReached);

UCLASS()
class CODINGCPP_API AMidnightRushGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
	AMidnightRushGameMode();

	/** Called by the Upload-Station each time drives are sent. */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void AddUploaded(int32 Amount);

	/** Blueprint can bind to this to display a win screen, etc. */
	UPROPERTY(BlueprintAssignable, Category = "Gameplay")
	FOnGoalReached OnGoalReached;

	/** How many drives must be uploaded to win. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
	int32 DrivesGoal = 10;

	/** Drives uploaded so far. */
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	int32 NumUploaded = 0;
};
