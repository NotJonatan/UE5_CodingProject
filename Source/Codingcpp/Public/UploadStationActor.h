// Source/Codingcpp/Public/UploadStationActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
//#include "UploadProgressWidget.h"
//#include "Components/WidgetComponent.h"
//#include "TimerManager.h"
#include "UploadStationActor.generated.h"

//Forward 
class UBoxComponent;
class UStaticMeshComponent;
class UWidgetComponent;
class UUploadProgressWidget;
class UInventoryComponent;


UCLASS()
class CODINGCPP_API AUploadStationActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	AUploadStationActor();

	/* IInteractableInterface */
	virtual void Interact_Implementation(AActor* Interactor) override;

	/** 0, 1 or 2 in the three placed actors */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Station")
	int32 StationID = 0;

	/** Drives the player must insert here */
	UPROPERTY(EditDefaultsOnly, Category = "Station")
	int32 DrivesRequired = 3;

protected:
	virtual void BeginPlay() override;
	void TickUpload();					// ← timer callback

	/* Trigger delegates */
	UFUNCTION()
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComp, AActor* Other,
		UPrimitiveComponent* OtherComp, int32 BodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerExit(UPrimitiveComponent* OverlappedComp, AActor* Other,
		UPrimitiveComponent* OtherComp, int32 BodyIndex);

	/* -- Upload runtime state -- */
	UPROPERTY(EditDefaultsOnly, Category = "Upload")
	float UploadDuration = 3.f;		// seconds for a full bar

	float		 Elapsed = 0.f;
	bool		 bUploading = false;
	bool		 bActivated = false;
	FTimerHandle UploadTimer;

	/* -- Components & widget -- */
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* StationMesh = nullptr;
	UPROPERTY(VisibleAnywhere) UBoxComponent* TriggerBox = nullptr;
	UPROPERTY(VisibleAnywhere) UWidgetComponent* ProgressComp = nullptr;	// widget component
	UUploadProgressWidget* ProgressWidget = nullptr;
};