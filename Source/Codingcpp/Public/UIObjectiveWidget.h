// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIObjectiveWidget.generated.h"

UCLASS()
class CODINGCPP_API UObjectiveWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnUploadedProgress(int32 Current, int32 Goal);
};