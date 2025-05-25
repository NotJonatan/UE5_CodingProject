#include "RailSplineActor.h"
#include "Components/SplineComponent.h"
//#include "Engine/World.h"  // for UWorld if you ever need it


ARailSplineActor::ARailSplineActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create & wire up the spline
	RailSpline = CreateDefaultSubobject<USplineComponent>(TEXT("RailSpline"));
	SetRootComponent(RailSpline);
}

USplineComponent* ARailSplineActor::GetSplineComponent() const
{
    return RailSpline;
}

int32 ARailSplineActor::GetNumberOfPoints() const
{
    return RailSpline ? RailSpline->GetNumberOfSplinePoints() : 0;
}

FVector ARailSplineActor::GetPointLocation(int32 PointIndex) const
{
    return RailSpline
        ? RailSpline->GetLocationAtSplinePoint(PointIndex, ESplineCoordinateSpace::World)
        : FVector::ZeroVector;
}