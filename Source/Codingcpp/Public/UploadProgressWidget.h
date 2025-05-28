// UploadProgressWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UploadProgressWidget.generated.h"

class UProgressBar;

UCLASS()
class CODINGCPP_API UUploadProgressWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    // Called when this widget is constructed; cache our ProgressBar pointer
    virtual void NativeConstruct() override;

    // Bind to the ProgressBar you placed in your UMG Designer
    UPROPERTY(meta = (BindWidget))
    UProgressBar* UploadBar;

public:
    /** Show & update the bar (0.0 → 1.0) */
    UFUNCTION(BlueprintCallable, Category = "Upload")
    void ShowUploadProgress(float Percent);

    /** Hide the bar when done or cancelled */
    UFUNCTION(BlueprintCallable, Category = "Upload")
    void HideUploadProgress();
};
