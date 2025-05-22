// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RailSplineActor.generated.h"

UCLASS()
class CODINGCPP_API ARailSplineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARailSplineActor();

	/** Returns location+tangent for a given alpha [0-1] */
	void GetPoint(float Alpha, FVector& OutLoc, FVector& OutTangent) const;

	USplineComponent* GetSpline() const { return RailSpline; }

private:
	UPROPERTY(VisibleAnywhere, Category = "Rail")
	USplineComponent* RailSpline;
};
