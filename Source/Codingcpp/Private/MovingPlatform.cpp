#include "MovingPlatform.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	if (!TargetPoint)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] has no TargetPoint set – it will not move."), *GetName());
	}
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetPoint) return;

	// decide which point to head to
	const FVector CurrentLoc = GetActorLocation();
	const FVector GoalLoc = bGoingToTarget
		? TargetPoint->GetActorLocation()
		: StartLocation;

	// move a little toward it
	const FVector Dir = (GoalLoc - CurrentLoc).GetSafeNormal();
	const FVector NewLoc = CurrentLoc + Dir * Speed * DeltaTime;
	SetActorLocation(NewLoc);

	// if we're close enough, flip
	const float Dist = FVector::Dist(CurrentLoc, GoalLoc);
	if (Dist < Threshold)
	{
		bGoingToTarget = !bGoingToTarget;
	}
}
