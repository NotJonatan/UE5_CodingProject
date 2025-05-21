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

void UInventoryComponent::UploadAllDrives()
{
    if (HardDrives.Num() > 0)
    {
        HardDrives.Empty();
        UE_LOG(LogTemp, Log, TEXT("All drives uploaded – inventory cleared"));
    }
}
