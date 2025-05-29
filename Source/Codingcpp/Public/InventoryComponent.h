// Source/Codingcpp/Public/InventoryComponent.h
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
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddHardDrive(AHardDriveActor* Drive);

    /** Upload everything currently in the drive array, return # uploaded */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 UploadAllDrives();

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
    bool HasRequiredDrives(int32 Amount) const { return HardDrives.Num() >= Amount; }

    /** Removes the first Amount drives from the array */
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void ConsumeHardDrives(int32 Amount);

    /** # of one-time Sandevistan uses the player holds */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sandevistan")
    int32 SandevistanCharges = 0;

    /** Grant one Sandevistan charge */
    UFUNCTION(BlueprintCallable, Category = "Sandevistan")
    void AddSandevistanCharge()
    {
        ++SandevistanCharges;
        UE_LOG(LogTemp, Log, TEXT("Picked up Sandevistan! Charges = %d"), SandevistanCharges);
    }

    /** Attempt to consume one Sandevistan charge */
    UFUNCTION(BlueprintCallable, Category = "Sandevistan")
    bool ConsumeSandevistanCharge()
    {
        if (SandevistanCharges > 0)
        {
            --SandevistanCharges;
            UE_LOG(LogTemp, Log, TEXT("Used Sandevistan. Remaining = %d"), SandevistanCharges);
            return true;
        }
        return false;
    }
};
