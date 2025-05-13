// Source/Codingcpp/Private/UploadStationActor.cpp
#include "UploadStationActor.h"
#include "Components/BoxComponent.h"
#include "InventoryComponent.h"
#include "GameFramework/Pawn.h"
#include "HardDriveActor.h"

AUploadStationActor::AUploadStationActor()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
}

void AUploadStationActor::Interact_Implementation(AActor* Interactor)
{
	if (APawn* Pawn = Cast<APawn>(Interactor))
	{
		if (UInventoryComponent* Inv = Pawn->FindComponentByClass<UInventoryComponent>())
		{
			// Upload & destroy all drives
			for (AHardDriveActor* Drive : Inv->GetHardDrives())
			{
				// Your upload logic here...
				Drive->Destroy();
			}
			Inv->ClearDrives();
		}
	}
}
