// HardDriveActor.cpp
#include "HardDriveActor.h"              // ← ALWAYS include your own header first
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "SprintCharacter.h"             // for the player class (forward declared in .h)
#include "InventoryComponent.h"

// ─────────────────────────────────────────────────────────────────────────────

AHardDriveActor::AHardDriveActor()
{
    /* Root & mesh --------------------------------------------------------- */
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    /* Trigger box --------------------------------------------------------- */
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->InitBoxExtent(FVector(20.f));

    // Register delegates
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AHardDriveActor::OnTriggerEnter);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AHardDriveActor::OnTriggerExit);
}

void AHardDriveActor::BeginPlay()
{
    Super::BeginPlay();
}

/* ── Overlap handlers ────────────────────────────────────────────────────── */
void AHardDriveActor::OnTriggerEnter(UPrimitiveComponent* /*OverlappedComp*/,
    AActor* OtherActor,
    UPrimitiveComponent* /*OtherComp*/,
    int32                /*OtherBodyIndex*/,
    bool                 /*bFromSweep*/,
    const FHitResult&    /*SweepResult*/)
{
    if (ASprintCharacter* Player = Cast<ASprintCharacter>(OtherActor))
    {
        if (UInventoryComponent* Inv = Player->FindComponentByClass<UInventoryComponent>())
        {
            Inv->AddHardDrive(this);             // your own function
            SetActorHiddenInGame(true);          // make it vanish after pickup
            SetActorEnableCollision(false);


        }
    }

    //if (GEngine)
    //{
    //    GEngine->AddOnScreenDebugMessage(
    //        -1,                           // key (-1 = new line)
    //        2.f,                          // time on screen
    //        FColor::Green,
    //        TEXT("Picked up Hard-Drive!") // message
    //    );
    //}
}


void AHardDriveActor::OnTriggerExit(UPrimitiveComponent* /*OverlappedComp*/,
    AActor*              /*OtherActor*/,
    UPrimitiveComponent* /*OtherComp*/,
    int32                /*OtherBodyIndex*/)
{
    /* nothing to do here – left empty intentionally                        */
}
