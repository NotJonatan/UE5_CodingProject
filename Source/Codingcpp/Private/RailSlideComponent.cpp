// RailSlideComponent.cpp
#include "RailSlideComponent.h"
#include "RailSplineActor.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"

URailSlideComponent::URailSlideComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    DistanceAlongSpline = 0.f;
}

void URailSlideComponent::BeginPlay()
{
    Super::BeginPlay();
    DistanceAlongSpline = 0.f;
}

void URailSlideComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!RailSplineActor || !RailSplineActor->RailSpline)
    {
        return;
    }

    DistanceAlongSpline += SlideSpeed * DeltaTime;
    const float SplineLength = RailSplineActor->RailSpline->GetSplineLength();
    if (DistanceAlongSpline > SplineLength)
    {
        DistanceAlongSpline = SplineLength;
    }

    FVector NewLoc = RailSplineActor->RailSpline->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
    FRotator NewRot = RailSplineActor->RailSpline->GetRotationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);

    if (AActor* Owner = GetOwner())
    {
        Owner->SetActorLocationAndRotation(NewLoc, NewRot);
    }
}
