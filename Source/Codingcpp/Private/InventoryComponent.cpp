// Source/Codingcpp/Private/InventoryComponent.cpp
#include "InventoryComponent.h"
#include "HardDriveActor.h"

UInventoryComponent::UInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::AddDrive(AHardDriveActor* Drive)
{
    if (Drive && !Drives.Contains(Drive))
    {
        Drives.Add(Drive);
        OnHardDriveAdded.Broadcast(Drive);
    }
}

bool UInventoryComponent::HasDrive() const
{
    return Drives.Num() > 0;
}
