// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UIPlayerHUD.generated.h"


class UObjectiveWidget;
class AMidnightRushGameMode;

UCLASS()
class CODINGCPP_API AMRHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	UFUNCTION() void HandleOverallProgress(int32 Current, int32 Goal);
	//UFUNCTION() void HandleStationProgress(int32 StationID, int32 Uploaded, int32 Goal);
	UFUNCTION() void HideProgress();
	FTimerHandle HideTimer;

	UPROPERTY()
	class UObjectiveWidget* ObjectiveWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;
};