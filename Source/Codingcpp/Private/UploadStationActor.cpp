// Source/Codingcpp/Private/UploadStationActor.cpp
#include "UploadStationActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "InventoryComponent.h"

AUploadStationActor::AUploadStationActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StationMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StationMesh"));
	SetRootComponent(StationMesh);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(60.f));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AUploadStationActor::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(
		this, &AUploadStationActor::OnTriggerEnter);
	TriggerBox->OnComponentEndOverlap.AddDynamic(
		this, &AUploadStationActor::OnTriggerExit);
}

void AUploadStationActor::Interact_Implementation(AActor* Interactor)
{
	if (ACharacter* Char = Cast<ACharacter>(Interactor))
	{
		if (UInventoryComponent* Inv = Char->FindComponentByClass<UInventoryComponent>())
		{
			Inv->UploadAllDrives();      // <-- implement inside InventoryComponent
		}
	}
}

void AUploadStationActor::OnTriggerEnter(
	UPrimitiveComponent* /*OverlappedComp*/,
	AActor* OtherActor,
	UPrimitiveComponent* /*OtherComp*/,
	int32                /*OtherBodyIndex*/,
	bool                 /*bFromSweep*/,
	const FHitResult&    /*SweepResult*/)
{
	if (ACharacter* Char = Cast<ACharacter>(OtherActor))
	{
		if (UInventoryComponent* Inv = Char->FindComponentByClass<UInventoryComponent>())
		{
			Inv->bInUploadRange = true;  // flag used by the player to enable UI prompt
		}
	}
}

void AUploadStationActor::OnTriggerExit(
	UPrimitiveComponent* /*OverlappedComp*/,
	AActor* OtherActor,
	UPrimitiveComponent* /*OtherComp*/,
	int32                /*OtherBodyIndex*/)
{
	if (ACharacter* Char = Cast<ACharacter>(OtherActor))
	{
		if (UInventoryComponent* Inv = Char->FindComponentByClass<UInventoryComponent>())
		{
			Inv->bInUploadRange = false;
		}
	}

	//if (GEngine)
	//{
	//	const int32 Num = InvComp->UploadAllDrives();
	//	GEngine->AddOnScreenDebugMessage(
	//		-1,
	//		2.f,
	//		FColor::Yellow,
	//		FString::Printf(TEXT("Uploaded %d drive(s)!"), Num)
	//	);
	//}
}
