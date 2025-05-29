#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MidnightRushGameMode.generated.h"

/* ───────── delegates ───────── */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUploadedProgress, int32, Current, int32, Goal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGoalReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameLost);          
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDied);

// forward so TSubclassOf<UUserWidget> compiles
class UUserWidget;

UCLASS()
class CODINGCPP_API AMidnightRushGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    /**  Called by a station when it successfully uploads one drive  */
    UFUNCTION() void RegisterUpload(int32 StationID);

    // Call this when the win condition is met
    void OnGameWon();

    /**  Fires for global 0-9 progress  */
    UPROPERTY(BlueprintAssignable) FOnUploadedProgress OnUploadedProgress;

    UPROPERTY(BlueprintAssignable) FOnPlayerDied OnPlayerDied;

    /*  Called by HealthComponent when player reaches 0 HP  */
    UFUNCTION() void NotifyPlayerDied();

    // Override to pick our custom spawn-point
    virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly) int32 DrivesPerStation = 3;
    UPROPERTY(EditDefaultsOnly) int32 NumStations = 3;

    /* Index 0-2 → drives already uploaded at that station         */
    UPROPERTY() TArray<int32> StationProgress;

    /* Total required to win (3×3 = 9)                             */
    UPROPERTY(EditDefaultsOnly) int32 DrivesGoal = 9;

    UPROPERTY(VisibleAnywhere)  int32 NumUploaded = 0;

    // Point this to your widget; set in Blueprint subclass of GameMode
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> YouWinWidgetClass;
};