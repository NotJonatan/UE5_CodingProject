// Source/Codingcpp/Public/UploadStationActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "UploadStationActor.generated.h"

class UBoxComponent;

UCLASS()
class CODINGCPP_API AUploadStationActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	AUploadStationActor();

	/** IInteractableInterface */
	virtual void Interact_Implementation(AActor* Interactor) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;
};
