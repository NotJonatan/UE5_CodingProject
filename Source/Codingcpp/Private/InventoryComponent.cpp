// Source/Codingcpp/Private/InventoryComponent.cpp
#include "InventoryComponent.h"
#include "HardDriveActor.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::AddDrive(AHardDriveActor* Drive)
{
	if (Drive && !HardDrives.Contains(Drive))
	{
		HardDrives.Add(Drive);
		OnHardDriveAdded.Broadcast(Drive);
	}
}

bool UInventoryComponent::HasDrive() const
{
	return HardDrives.Num() > 0;
}

void UInventoryComponent::ClearDrives()
{
	HardDrives.Empty();
}