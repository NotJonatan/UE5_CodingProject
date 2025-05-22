// Fill out your copyright notice in the Description page of Project Settings.
#include "RailSplineActor.h"
#include "Components/SplineComponent.h"

ARailSplineActor::ARailSplineActor()
{
	RailSpline = CreateDefaultSubobject<USplineComponent>(TEXT("RailSpline"));
	SetRootComponent(RailSpline);
}

void ARailSplineActor::GetPoint(float Alpha, FVector& OutLoc, FVector& OutTangent) const
{
	if (!RailSpline) { OutLoc = OutTangent = FVector::ZeroVector; return; }
	const float Distance = RailSpline->GetSplineLength() * FMath::Clamp(Alpha, 0.f, 1.f);
	OutLoc = RailSpline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	OutTangent = RailSpline->GetTangentAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
}
