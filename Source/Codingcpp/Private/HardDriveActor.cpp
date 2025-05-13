// Source/Codingcpp/Private/HardDriveActor.cpp
#include "HardDriveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "InventoryComponent.h"

AHardDriveActor::AHardDriveActor()
{
	PrimaryActorTick.bCanEverTick = false;

	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
	RootComponent = PickupSphere;
	PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &AHardDriveActor::OnSphereOverlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(PickupSphere);
}

void AHardDriveActor::BeginPlay()
{
	Super::BeginPlay();
}

void AHardDriveActor::OnSphereOverlap(
	UPrimitiveComponent* /*OverlappedComp*/,
	AActor* OtherActor,
	UPrimitiveComponent* /*OtherComp*/,
	int32 /*OtherBodyIndex*/,
	bool /*bFromSweep*/,
	const FHitResult& /*SweepResult*/
)
{
	if (UInventoryComponent* Inv = OtherActor->FindComponentByClass<UInventoryComponent>())
	{
		Inv->AddDrive(this);
		Destroy();
	}
}

void AHardDriveActor::Interact_Implementation(AActor* Interactor)
{
	if (UInventoryComponent* Inv = Interactor->FindComponentByClass<UInventoryComponent>())
	{
		Inv->AddDrive(this);
		Destroy();
	}
}
