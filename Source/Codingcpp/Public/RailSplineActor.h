// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "RailSplineActor.generated.h"

class USplineComponenet;

UCLASS()
class CODINGCPP_API ARailSplineActor : public AActor
{
	GENERATED_BODY()
	
public:	
    ARailSplineActor();

    /** The spline we ride along */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rail")
    USplineComponent* RailSpline;

    /** Public getter so other classes/components can grab the spline */
    UFUNCTION(BlueprintCallable, Category = "Rail")
    USplineComponent* GetSplineComponent() const;

    /** Helper to ask “how many points” */
    UFUNCTION(BlueprintCallable, Category = "Rail")
    int32 GetNumberOfPoints() const;

    /** Helper to fetch the world‐space location at a given point */
    UFUNCTION(BlueprintCallable, Category = "Rail")
    FVector GetPointLocation(int32 PointIndex) const;
};
