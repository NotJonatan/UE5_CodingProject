#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class CODINGCPP_API AHealthPickup : public AActor
{
    GENERATED_BODY()

public:
    AHealthPickup();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    USphereComponent* CollisionComp;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;

    /** amount to heal */
    UPROPERTY(EditAnywhere, Category = "Pickup")
    float HealAmount = 50.f;

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
