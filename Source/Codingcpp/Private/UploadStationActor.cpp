// Source/Codingcpp/Private/UploadStationActor.cpp
#include "UploadStationActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "InventoryComponent.h"
#include "Engine/Engine.h"
#include "Components/WidgetComponent.h"          //   add
#include "TimerManager.h"                        //   add
#include "MidnightRushGameMode.h"
#include "UploadProgressWidget.h"
#include "Engine/World.h"


AUploadStationActor::AUploadStationActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StationMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = StationMesh;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("Trigger");
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->InitBoxExtent(FVector(100.f));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TriggerBox->SetGenerateOverlapEvents(true);

	// BIND DELEGATES (don’t leave commented)
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AUploadStationActor::OnTriggerEnter);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AUploadStationActor::OnTriggerExit);

	//Progress Bar
	ProgressComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("ProgressWidget"));
	ProgressComp->SetupAttachment(RootComponent);
	ProgressComp->SetWidgetSpace(EWidgetSpace::Screen);
	ProgressComp->SetDrawSize(FVector2D(120.f, 15.f));
	// you can set the widget class here or in BeginPlay:
	ProgressComp->SetWidgetClass(UUploadProgressWidget::StaticClass());
	ProgressComp->SetVisibility(false);
}

void AUploadStationActor::BeginPlay()
{
	Super::BeginPlay();

	//already set the overlap trigger boxes in the constructor. this isn't needed anymore
	//TriggerBox->OnComponentBeginOverlap.AddDynamic(
	//	this, &AUploadStationActor::OnTriggerEnter);
	//TriggerBox->OnComponentEndOverlap.AddDynamic(
	//	this, &AUploadStationActor::OnTriggerExit);

	ProgressComp->SetWidgetClass(UUploadProgressWidget::StaticClass());
	ProgressWidget = Cast<UUploadProgressWidget>(ProgressComp->GetUserWidgetObject());          // hidden until uploading
}

void AUploadStationActor::TickUpload()
{
	Elapsed += 0.05f;
	const float Alpha = Elapsed / UploadDuration;

	if (ProgressWidget)
	{
		// update the *station’s* progress bar
		ProgressWidget->ShowUploadProgress(Elapsed / UploadDuration);
	}

	if (Alpha >= 1.f)
	{
		// stop the station bar
		GetWorldTimerManager().ClearTimer(UploadTimer);
		ProgressComp->SetVisibility(false);
		bUploading = false;
		bActivated = true;

		// **now** tell the GameMode this station finished
		if (AMidnightRushGameMode* GM = GetWorld()->GetAuthGameMode<AMidnightRushGameMode>())
		{
			GM->RegisterUpload(StationID);
		}

		// hide the station bar completely (via your widget)
		if (ProgressWidget)
		{
			ProgressWidget->HideUploadProgress();
		}
	}
}


/* -- player pressed E -- */
void AUploadStationActor::Interact_Implementation(AActor* Interactor)
{
    UE_LOG(LogTemp, Log, TEXT("[Station] Interact called by %s"), *Interactor->GetName());

    if (bActivated) return;

    UInventoryComponent* Inv = Interactor->FindComponentByClass<UInventoryComponent>();
    if (!Inv || !Inv->HasRequiredDrives(DrivesRequired)) return;

    Inv->ConsumeHardDrives(DrivesRequired);

    if (AMidnightRushGameMode* GM = GetWorld()->GetAuthGameMode<AMidnightRushGameMode>())
    {
        GM->RegisterUpload(StationID);      // single call increments all the delegates :contentReference[oaicite:0]{index=0}
    }

	/* kick-off upload */
	bUploading = true;
	Elapsed = 0.f;
	ProgressComp->SetVisibility(true);
	GetWorldTimerManager().SetTimer(
		UploadTimer, this,
		&AUploadStationActor::TickUpload,    /* function */
		0.05f,                               /* 20 fps */
		true);

    bActivated = true;
}

void AUploadStationActor::OnTriggerEnter(
	UPrimitiveComponent*, AActor* Other, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	if (ACharacter* Char = Cast<ACharacter>(Other))
	{
		if (UInventoryComponent* Inv = Char->FindComponentByClass<UInventoryComponent>())
		{
			Inv->bInUploadRange = true;              // << use Inv->

			UE_LOG(LogTemp, Log, TEXT("[Station] overlap enter by %s"), *Other->GetName());
		}
	}
}

void AUploadStationActor::OnTriggerExit(
	UPrimitiveComponent*, AActor* Other, UPrimitiveComponent*, int32)
{
	if (ACharacter* Char = Cast<ACharacter>(Other))
	{
		if (UInventoryComponent* Inv = Char->FindComponentByClass<UInventoryComponent>())
		{
			Inv->bInUploadRange = false;             // << use Inv->
		}
	}
}
