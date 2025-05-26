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

	/* delegate handlers */
	UFUNCTION() void HandleOverallProgress(int32 Current, int32 Goal);
	UFUNCTION() void HandleHealth(float NewHealth, float Delta);
	UFUNCTION() void HideUploadBar();

private:
	FTimerHandle HideTimer;

	UPROPERTY() UObjectiveWidget* ObjectiveWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;
};