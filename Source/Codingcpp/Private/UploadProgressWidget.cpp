// UploadProgressWidget.cpp
#include "UploadProgressWidget.h"
#include "Components/ProgressBar.h"

void UUploadProgressWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (UploadBar)
    {
        UploadBar->SetPercent(0.f);
        UploadBar->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UUploadProgressWidget::ShowUploadProgress(float Percent)
{
    if (UploadBar)
    {
        UploadBar->SetVisibility(ESlateVisibility::Visible);
        UploadBar->SetPercent(FMath::Clamp(Percent, 0.f, 1.f));
    }
}

void UUploadProgressWidget::HideUploadProgress()
{
    if (UploadBar)
    {
        UploadBar->SetVisibility(ESlateVisibility::Hidden);
    }
}
