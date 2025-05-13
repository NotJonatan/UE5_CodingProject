// Source/Codingcpp/Public/InventoryComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AHardDriveActor;

// Fired when you successfully add a drive
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

private:
    /** Stored drives */
    UPROPERTY()
    TArray<AHardDriveActor*> Drives;
};
