// Source/Codingcpp/Public/HardDriveActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "HardDriveActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class CODINGCPP_API AHardDriveActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	AHardDriveActor();

	/** IInteractableInterface */
	virtual void Interact_Implementation(AActor* Interactor) override;

protected:
	virtual void BeginPlay() override;

	/** Sphere for detecting pickups */
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* PickupSphere;

	/** Visual mesh */
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	UStaticMeshComponent* MeshComp;

	/** Called on overlap */
	UFUNCTION()
	void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
