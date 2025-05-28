#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RailSplineActor.generated.h"

class USplineComponent;
class USplineMeshComponent;

UCLASS()
class CODINGCPP_API ARailSplineActor : public AActor
{
	GENERATED_BODY()

public:
	ARailSplineActor();

	// whenever you move spline points in the editor this will re‐build the rails
	virtual void OnConstruction(const FTransform& Transform) override;

	// the spline you lay out in BP
	UPROPERTY(VisibleAnywhere, Category = "Rail")
	USplineComponent* RailSpline;

	// pick your mesh in the details panel
	UPROPERTY(EditAnywhere, Category = "Rail")
	UStaticMesh* SegmentMesh;

	// optional: pick a material if you want
	UPROPERTY(EditAnywhere, Category = "Rail")
	UMaterialInterface* SegmentMaterial;

	// the runtime spline‐mesh components
	UPROPERTY()
	TArray<USplineMeshComponent*> SplineMeshes;
};
