#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SandevistanPickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class CODINGCPP_API ASandevistanPickup : public AActor
{
    GENERATED_BODY()

public:
    ASandevistanPickup();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    USphereComponent* CollisionComp;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;

    UFUNCTION()
    void OnOverlap(
        UPrimitiveComponent* Overlapped,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& Sweep
    );
};
