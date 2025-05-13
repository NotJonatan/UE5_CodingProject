// Source/Codingcpp/Public/InventoryComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AHardDriveActor;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHardDriveAdded, AHardDriveActor*, Drive);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CODINGCPP_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	/** Add a drive to our inventory (if not already present) */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddDrive(AHardDriveActor* Drive);

	/** True if inventory has at least one drive */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasDrive() const;

	/** Broadcast when a drive is added */
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnHardDriveAdded OnHardDriveAdded;

	/** Read-only access to the internal array */
	const TArray<AHardDriveActor*>& GetHardDrives() const { return HardDrives; }

	/** Remove all drives (called after upload) */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ClearDrives();

protected:
	/** Under-the-hood storage */
	UPROPERTY()
	TArray<AHardDriveActor*> HardDrives;
};
