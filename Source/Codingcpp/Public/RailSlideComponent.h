// RailSlideComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RailSlideComponent.generated.h"

class ARailSplineActor;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CODINGCPP_API URailSlideComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    URailSlideComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // The spline actor we slide along
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rail")
    ARailSplineActor* RailSplineActor;

    // Speed (units per second)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rail")
    float SlideSpeed = 100.f;

private:
    // Distance traveled along the spline
    float DistanceAlongSpline;
};