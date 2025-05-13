// Source/Codingcpp/Public/HardDriveActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HardDriveActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UInventoryComponent;

UCLASS()
class CODINGCPP_API AHardDriveActor : public AActor
{
    GENERATED_BODY()

public:
    AHardDriveActor();

protected:
    virtual void BeginPlay() override;

    /** Sphere for detecting the player */
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* PickupSphere;

    /** Visible mesh */
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    UStaticMeshComponent* MeshComp;

    /** Called when something overlaps PickupSphere */
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
