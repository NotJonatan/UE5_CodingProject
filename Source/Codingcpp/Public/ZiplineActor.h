// ZiplineActor.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZiplineActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class ACharacter;

UCLASS()
class CODINGCPP_API AZiplineActor : public AActor
{
	GENERATED_BODY()

public:
	AZiplineActor();

    /** World-space start / end of the cable */
    UPROPERTY(EditAnywhere, Category = "Zipline")
    FVector LineStart = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, Category = "Zipline")
    FVector LineEnd = FVector(0.f, 0.f, 300.f);

    /** Units/second the rider moves */
    UPROPERTY(EditDefaultsOnly, Category = "Zipline")
    float SlideSpeed = 900.f;

protected:
    virtual void Tick(float DeltaTime) override;

    /** Trigger overlap entry */
    UFUNCTION()
    void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other,
        UPrimitiveComponent* OtherComp, int32 BodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    /** Helpers */
    FORCEINLINE FVector GetPoint(float Alpha) const
    {
        return FMath::Lerp(LineStart, LineEnd, Alpha);
    }

    /* Components */
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Cable;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* Trigger;

    /* Runtime state */
    ACharacter* RidingChar = nullptr;
    float       Progress = 0.f;          // 0-1 along cable
};