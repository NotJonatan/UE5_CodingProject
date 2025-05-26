#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MidnightRushGameMode.generated.h"

/* ───────── delegates ───────── */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnUploadedProgress,            // overall uploads
    int32, Current,
    int32, Goal);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(             // win event
    FOnGoalReached);
/* ───────────────────────────── */

UCLASS()
class CODINGCPP_API AMidnightRushGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    /** Adds Amount drives, fires progress / win events */
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void AddUploaded(int32 Amount);

    UPROPERTY(BlueprintAssignable, Category = "Gameplay")
    FOnUploadedProgress OnUploadedProgress;

    UPROPERTY(BlueprintAssignable, Category = "Gameplay")
    FOnGoalReached      OnGoalReached;

    /** Drives required in total (3 stations × 3 drives) */
    UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
    int32 DrivesGoal = 9;

    /** Drives uploaded so far */
    UPROPERTY(VisibleAnywhere, Category = "Gameplay")
    int32 NumUploaded = 0;
};
