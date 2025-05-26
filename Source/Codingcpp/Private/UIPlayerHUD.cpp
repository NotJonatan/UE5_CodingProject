// Fill out your copyright notice in the Description page of Project Settings.
#include "UIPlayerHUD.h"
#include "UIObjectiveWidget.h"
#include "MidnightRushGameMode.h"
#include "TimerManager.h"

void AMRHUD::BeginPlay()
{
    Super::BeginPlay();

    ObjectiveWidget = CreateWidget<UObjectiveWidget>(
        GetWorld(), ObjectiveWidgetClass);
    if (ObjectiveWidget) ObjectiveWidget->AddToViewport();

    // Bind global progress (0-9)
    if (auto* GM = GetWorld()->GetAuthGameMode<AMidnightRushGameMode>())
    {
        GM->OnUploadedProgress.AddDynamic(
            this, &AMRHUD::HandleOverallProgress);

        //GM->OnStationProgress.AddDynamic(
        //    this, &AMRHUD::HandleStationProgress);
    }
}

//void AMRHUD::HandleStationProgress(int32 StationID, int32 Uploaded, int32 Goal)
//{
//    if (!ObjectiveWidget || Uploaded == 0) return;
//
//    const float Percent = static_cast<float>(Uploaded) / Goal;
//    ObjectiveWidget->ShowUploadProgress(Percent);
//
//    // Auto-hide one second after a FULL upload (3/3)
//    if (Percent >= 1.f)
//    {
//        GetWorld()->GetTimerManager()
//            .SetTimer(HideTimer, this, &AMRHUD::HideProgress, 1.f, false);
//    }
//}

void AMRHUD::HandleOverallProgress(int32 /*Current*/, int32 /*Goal*/)
{
    // You can leave this empty for now
}

void AMRHUD::HideProgress()
{
    if (ObjectiveWidget) ObjectiveWidget->HideUploadProgress();
}