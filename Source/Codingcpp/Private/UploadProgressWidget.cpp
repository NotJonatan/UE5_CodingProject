// Fill out your copyright notice in the Description page of Project Settings.


#include "UploadProgressWidget.h"

#include "Components/ProgressBar.h"

void UUploadProgressWidget::SetProgress(float InPercent)
{
    if (UploadBar)
    {
        UploadBar->SetPercent(FMath::Clamp(InPercent, 0.f, 1.f));
    }
}