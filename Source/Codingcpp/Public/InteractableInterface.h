// Source/Codingcpp/Public/InteractableInterface.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

UINTERFACE(Blueprintable)
class CODINGCPP_API UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/** Anything the player can “E” interact with */
class CODINGCPP_API IInteractableInterface
{
	GENERATED_BODY()

public:
	/** Called when someone presses E on this object */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(AActor* Interactor);
};
