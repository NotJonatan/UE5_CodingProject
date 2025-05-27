#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MidnightRushGameMode.generated.h"

/* ───────── delegates ───────── */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUploadedProgress, int32, Current, int32, Goal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGoalReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameLost);          //

UCLASS()
class CODINGCPP_API AMidnightRushGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    /* called by stations */
    void AddUploaded(int32 Amount);

    /* events the HUD binds to */
    UPROPERTY(BlueprintAssignable) FOnUploadedProgress OnUploadedProgress;
    UPROPERTY(BlueprintAssignable) FOnGoalReached      OnGoalReached;
    UPROPERTY(BlueprintAssignable) FOnGameLost         OnGameLost;       // 

    /* damage reporting from HealthComponent */
    void NotifyPlayerDied();                                            // 

protected:
    UPROPERTY(EditDefaultsOnly) int32 DrivesGoal = 9;
    UPROPERTY(VisibleAnywhere)  int32 NumUploaded = 0;
};