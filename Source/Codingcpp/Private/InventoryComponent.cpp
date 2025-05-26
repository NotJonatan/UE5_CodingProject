// InventoryComponent.cpp
#include "InventoryComponent.h"
#include "HardDriveActor.h"          // needs the forward-declared class

UInventoryComponent::UInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

/* ------------------------------------------------------------------------- */
void UInventoryComponent::AddHardDrive(AHardDriveActor* Drive)
{
    if (Drive && !HardDrives.Contains(Drive))
    {
        HardDrives.Add(Drive);
        UE_LOG(LogTemp, Log, TEXT("Drive picked up – total now: %d"), HardDrives.Num());
    }
}

int32 UInventoryComponent::UploadAllDrives()
{
    const int32 Count = HardDrives.Num();
    HardDrives.Empty();

    // any extra logic you want…

    return Count;
}

void UInventoryComponent::ConsumeHardDrives(int32 Amount)
{
    Amount = FMath::Min(Amount, HardDrives.Num());
    HardDrives.RemoveAt(/*StartIdx=*/0, Amount, /*bAllowShrinking=*/true);
}