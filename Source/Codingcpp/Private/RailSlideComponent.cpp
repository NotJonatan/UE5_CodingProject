#include "RailSlideComponent.h"
#include "RailSplineActor.h"
#include "Components/SplineComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

URailSlideComponent::URailSlideComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URailSlideComponent::BeginPlay()
{
	Super::BeginPlay();
}

void URailSlideComponent::StartSliding(ARailSplineActor* RailActor)
{
	if (!RailActor) return;

	// grab the spline
	CurrentSpline = RailActor->GetSplineComponent();
	CurrentDistance = 0.f;

	// start our recurring timer
	GetWorld()->GetTimerManager().SetTimer(
		SlideTimerHandle,
		this,
		&URailSlideComponent::HandleSlide,
		TickInterval,
		true
	);
}

void URailSlideComponent::StopSliding()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(SlideTimerHandle);
	}
	CurrentSpline = nullptr;
}

void URailSlideComponent::HandleSlide()
{
	if (!CurrentSpline)
	{
		StopSliding();
		return;
	}

	// advance our distance
	CurrentDistance += SlideSpeed * TickInterval;

	// check for end of spline
	const float SplineLen = CurrentSpline->GetSplineLength();
	if (CurrentDistance >= SplineLen)
	{
		StopSliding();
		return;
	}

	// compute new location & rotation
	FVector NewLoc = CurrentSpline->GetLocationAtDistanceAlongSpline(
		CurrentDistance, ESplineCoordinateSpace::World);
	FRotator NewRot = CurrentSpline->GetRotationAtDistanceAlongSpline(
		CurrentDistance, ESplineCoordinateSpace::World);

	// apply to owner
	if (AActor* Owner = GetOwner())
	{
		Owner->SetActorLocationAndRotation(NewLoc, NewRot);
	}
}
