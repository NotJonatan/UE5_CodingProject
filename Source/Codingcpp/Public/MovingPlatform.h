#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class CODINGCPP_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	// Assign this in the editor to the “other” point you want to move toward.
	UPROPERTY(EditInstanceOnly, Category = "Movement")
	AActor* TargetPoint = nullptr;

	// Speed in units/sec
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "0.0"))
	float Speed = 200.f;

	// How close before flipping direction
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "0.0"))
	float Threshold = 10.f;

private:
	// Remember where we started
	FVector StartLocation;

	// Which way are we heading?
	bool bGoingToTarget = true;
};
