// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UploadProgressWidget.generated.h"

class UProgressBar;

UCLASS()
class CODINGCPP_API UUploadProgressWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /** 0-1 range */
    UFUNCTION(BlueprintCallable)
    void SetProgress(float InPercent);

protected:
    /** Bind to the ProgressBar you place in the WBP. */
    UPROPERTY(meta = (BindWidget))
    UProgressBar* UploadBar = nullptr;
};