// HardDriveActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HardDriveActor.generated.h"

    // ── forward-declarations ──────────────────────────
class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class CODINGCPP_API AHardDriveActor : public AActor
{
    GENERATED_BODY()

public:
    AHardDriveActor();

protected:
    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HardDrive")
    UStaticMeshComponent* Mesh = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HardDrive")
    UBoxComponent* TriggerBox = nullptr;

    // AActor interface
    virtual void BeginPlay() override;

    /* Trigger delegates ---------------------------------------------------- */
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
};
