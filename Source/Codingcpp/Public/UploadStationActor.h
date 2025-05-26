// Source/Codingcpp/Public/UploadStationActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "UploadStationActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UInventoryComponent;


UCLASS()
class CODINGCPP_API AUploadStationActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	AUploadStationActor();

	/* IInteractableInterface */
	virtual void Interact_Implementation(AActor* Interactor) override;

	UPROPERTY(EditInstanceOnly, Category = "Station")
	int32 StationID = 0;    // 0,1,2 in your three placed actors

	// NEW editable setting
	UPROPERTY(EditDefaultsOnly, Category = "Station")
	int32 DrivesRequired = 3;

	bool bActivated = false;            // becomes true after first (and only) upload burst

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32                OtherBodyIndex,
		bool                 bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerExit(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32                OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StationMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;
};