#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "SandevistanPickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UParticleSystem;

UCLASS()
class CODINGCPP_API ASandevistanPickup : public AActor
{
    GENERATED_BODY()

public:
    ASandevistanPickup();

protected:
    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


    UPROPERTY(VisibleAnywhere)
    USphereComponent* CollisionComp;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;

    /** Drag-and-drop your VFX asset onto this in Blueprint. */
    UPROPERTY(EditAnywhere, Category = "Sandevistan")
    UParticleSystem* SandevistanVFX;

    //NOT USING ONOVERLAP -> WE MOVED IT TO virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
//    UFUNCTION()
//    void OnOverlap(
//        UPrimitiveComponent* Overlapped,
//        AActor* OtherActor,
//        UPrimitiveComponent* OtherComp,
//        int32 OtherBodyIndex,
//        bool bFromSweep,
//        const FHitResult& Sweep
//    );
};
