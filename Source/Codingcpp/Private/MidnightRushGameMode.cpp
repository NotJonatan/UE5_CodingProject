// Source/Codingcpp/Private/MidnightRushGameMode.cpp
#include "MidnightRushGameMode.h"
//#include "Codingcpp.h"                             // causes error if this isn't first library
//#include "SprintCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"



AActor* AMidnightRushGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
    // Search by tag:
    static const FName RespawnTag(TEXT("Respawn"));
    TArray<AActor*> Found;
    UGameplayStatics::GetAllActorsWithTag(this, RespawnTag, Found);

    if (Found.Num() > 0)
    {
        return Found[0];
    }
    return Super::ChoosePlayerStart_Implementation(Player);
}

void AMidnightRushGameMode::BeginPlay()
{
    Super::BeginPlay();
    StationProgress.Init(0, NumStations);   //  [0,0,0]
}

void AMidnightRushGameMode::RegisterUpload(int32 StationID)
{
    if (!StationProgress.IsValidIndex(StationID)) return;
    if (StationProgress[StationID] >= DrivesPerStation) return;   // already full

    StationProgress[StationID] += 1;
    NumUploaded += 1;

    UE_LOG(LogTemp, Log, TEXT("[GM] Station %d ++  (%d / %d total)"),
        StationID, NumUploaded, DrivesGoal);

    OnUploadedProgress.Broadcast(NumUploaded, DrivesGoal);

    if (NumUploaded >= DrivesGoal)
    {
        UE_LOG(LogTemp, Log, TEXT("[GM] All drives uploaded – WIN"));

        // ← Add this call to trigger your UI
        OnGameWon();
    }
}

void AMidnightRushGameMode::NotifyPlayerDied()
{
    UE_LOG(LogTemp, Warning, TEXT("[GM] Player died – fail state"));
    OnPlayerDied.Broadcast();       // does nothing if nobody bound
}

void AMidnightRushGameMode::OnGameWon()
{
    UE_LOG(LogTemp, Log, TEXT("[GM] OnGameWon()"));

    if (YouWinWidgetClass == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("OnGameWon: YouWinWidgetClass not set!"));
        return;
    }

    // Grab the first player controller
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (!PC)
    {
        UE_LOG(LogTemp, Warning, TEXT("OnGameWon: No PlayerController found"));
        return;
    }

    // Create and show the widget
    UUserWidget* WinScreen = CreateWidget<UUserWidget>(PC, YouWinWidgetClass);
    if (WinScreen)
    {
        WinScreen->AddToViewport();
        PC->SetPause(true);
        PC->bShowMouseCursor = true;
        PC->SetInputMode(FInputModeUIOnly());
    }
}