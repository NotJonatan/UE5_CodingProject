// Fill out your copyright notice in the Description page of Project Settings.
#include "UIPlayerHUD.h"
#include "UIObjectiveWidget.h"
#include "MidnightRushGameMode.h"
#include "TimerManager.h"
#include "HealthComponent.h"

void AMRHUD::BeginPlay()
{
    Super::BeginPlay();

    ObjectiveWidget = CreateWidget<UObjectiveWidget>(
        GetWorld(), ObjectiveWidgetClass);
    if (ObjectiveWidget) ObjectiveWidget->AddToViewport();

    // Bind health bar
    if(APawn* Pawn = GetOwningPawn())
    {
        if (UHealthComponent* HC = Pawn->FindComponentByClass<UHealthComponent>())
        {
            HC->OnHealthChanged.AddDynamic(this, &AMRHUD::HandleHealth);
        }
    }

     // Bind drive progress / win
    if (auto* GM = GetWorld()->GetAuthGameMode<AMidnightRushGameMode>())
        GM->OnUploadedProgress.AddDynamic(this, &AMRHUD::HandleOverallProgress);

    // Bind global progress (0-9)
    if (auto* GM = GetWorld()->GetAuthGameMode<AMidnightRushGameMode>())
    {
        GM->OnUploadedProgress.AddDynamic(
            this, &AMRHUD::HandleOverallProgress);

        //GM->OnStationProgress.AddDynamic(
        //    this, &AMRHUD::HandleStationProgress);
    }
}
//WE DON'T NEED THIS ANYMORE.
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


/* Handles 0-9 drive pickups */
void AMRHUD::HandleOverallProgress(int32 Current, int32 Goal)
{
    if (!ObjectiveWidget) return;
    const float Percent = static_cast<float>(Current) / Goal;
    ObjectiveWidget->ShowUploadProgress(Percent);

    /* hide after 1 s when full */
    if (Percent >= 1.f)
        GetWorld()->GetTimerManager().SetTimer(
            HideTimer, this, &AMRHUD::HideUploadBar, 1.f, false);
}

// hide upload bar
void AMRHUD::HideUploadBar()
{
    if (ObjectiveWidget) ObjectiveWidget->HideUploadProgress();
}

void AMRHUD::HandleHealth(float NewHealth, float Delta)
{
    if (ObjectiveWidget)
        ObjectiveWidget->ShowHealth(NewHealth);   // BlueprintImplementableEvent
}