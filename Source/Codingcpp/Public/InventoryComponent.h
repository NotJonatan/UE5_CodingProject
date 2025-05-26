// InventoryComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

/* forward declaration to avoid circular include */
class AHardDriveActor;

#include "InventoryComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CODINGCPP_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInventoryComponent();

    /* ---------------- inventory API ---------------- */

    /** Add a drive to the player’s list (called from AHardDriveActor) */
    void AddHardDrive(AHardDriveActor* Drive);

    /** Upload everything currently in the drive array, return # uploaded */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 UploadAllDrives();  // <-- single, final declaration

    /** Has the player stepped into an upload station’s trigger? */
    UPROPERTY(BlueprintReadWrite, Category = "Inventory")
    bool bInUploadRange = false;

    /** Drives currently carried by the player */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<AHardDriveActor*> HardDrives;

    /** Current number of drives the player holds */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetHardDriveCount() const { return HardDrives.Num(); }

    /** True if the player holds at least Amount drives */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool HasRequiredDrives(int32 Amount) const
    {
        return HardDrives.Num() >= Amount;
    }

    /** Removes the first Amount drives from the array */
    void ConsumeHardDrives(int32 Amount);


};
