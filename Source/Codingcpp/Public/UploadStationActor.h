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