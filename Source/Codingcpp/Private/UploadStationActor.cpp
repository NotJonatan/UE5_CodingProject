// Source/Codingcpp/Private/UploadStationActor.cpp
#include "UploadStationActor.h"    // first include!
#include "Components/BoxComponent.h"
#include "InventoryComponent.h"
#include "GameFramework/Character.h"

AUploadStationActor::AUploadStationActor()
{
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AUploadStationActor::OnBoxOverlap);
}

void AUploadStationActor::BeginPlay()
{
    Super::BeginPlay();
}

void AUploadStationActor::OnBoxOverlap(
    UPrimitiveComponent* /*OverlappedComp*/,
    AActor* OtherActor,
    UPrimitiveComponent* /*OtherComp*/,
    int32 /*OtherBodyIndex*/,
    bool /*bFromSweep*/,
    const FHitResult& /*Sweep*/
)
{
    if (ACharacter* Char = Cast<ACharacter>(OtherActor))
    {
        if (UInventoryComponent* Inv = Char->FindComponentByClass<UInventoryComponent>())
        {
            if (Inv->HasDrive())
            {
                OnUploadCompleted.Broadcast();
            }
        }
    }
}
