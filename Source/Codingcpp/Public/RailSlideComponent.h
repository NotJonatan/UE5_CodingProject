#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RailSlideComponent.generated.h"

class ARailSplineActor;
class UCharacterMovementComponent;

UCLASS(ClassGroup = (Movement), meta = (BlueprintSpawnableComponent))
class CODINGCPP_API URailSlideComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URailSlideComponent();

	/** Call when player presses the “grind” key near a rail. */
	bool TryStartSlide(ARailSplineActor* Rail, float StartAlpha);

	/** To be ticked from owning pawn */
	void TickSlide(float DeltaTime);

	/** Breaks the slide immediately */
	void EndSlide();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ARailSplineActor* CurrentRail = nullptr;

	float SlideAlpha = 0.f;
	float SlideSpeed = 600.f;     // units per second along spline
	bool  bSliding = false;

	UCharacterMovementComponent* MoveComp = nullptr;
};
