// Source/Codingcpp/Private/HardDriveActor.cpp
#include "HardDriveActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "SprintCharacter.h"
#include "InventoryComponent.h"
#include "Engine/Engine.h"

AHardDriveActor::AHardDriveActor()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Root mesh --------------------------------------------------------- */
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	/* Trigger box ------------------------------------------------------- */
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(20.f));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	/* Delegate bindings ------------------------------------------------- */
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AHardDriveActor::OnTriggerEnter);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AHardDriveActor::OnTriggerExit);
}

void AHardDriveActor::BeginPlay()
{
	Super::BeginPlay();
}

/* ─────────────────────────────────────────────────────────────── */
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
            Inv->AddHardDrive(this);          // <-- call; no return value to test

            /* Feedback -------------------------------------------------- */
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(
                    -1, 2.f, FColor::Green, TEXT("Picked up Hard-Drive"));
            }

            /* Hide / disable the actor so it can’t be picked twice ------ */
            SetActorEnableCollision(false);
            SetActorHiddenInGame(true);
        }
    }
}


void AHardDriveActor::OnTriggerExit(UPrimitiveComponent* /*OverlappedComp*/,
	AActor*              /*OtherActor*/,
	UPrimitiveComponent* /*OtherComp*/,
	int32                /*OtherBodyIndex*/)
{
	// Nothing needed here for now
}
