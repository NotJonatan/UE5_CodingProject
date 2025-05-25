#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RailSlideComponent.generated.h"

class ARailSplineActor;
class USplineComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CODINGCPP_API URailSlideComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URailSlideComponent();

	virtual void BeginPlay() override;

	/** Kick off sliding along the given rail */
	void StartSliding(ARailSplineActor* RailActor);

	/** Immediately stop sliding */
	void StopSliding();

protected:
	/** Called each tick of our timer to advance along the spline */
	void HandleSlide();

	/** Movement speed along the rail (units/sec) */
	UPROPERTY(EditAnywhere, Category = "RailSlide")
	float SlideSpeed = 600.f;

	/** How often (seconds) to update our position */
	UPROPERTY(EditAnywhere, Category = "RailSlide")
	float TickInterval = 0.02f;

private:
	/** The spline we’re currently riding */
	USplineComponent* CurrentSpline = nullptr;

	/** How far along (distance) we’ve already moved */
	float CurrentDistance = 0.f;

	/** Timer handle so we can cancel when we reach the end */
	FTimerHandle SlideTimerHandle;
};