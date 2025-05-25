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

	UPROPERTY(EditDefaultsOnly) TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;

private:
	UPROPERTY() UObjectiveWidget* ObjectiveWidget = nullptr;

	UFUNCTION()
	void HandleProgress(int32 Current, int32 Goal);
};