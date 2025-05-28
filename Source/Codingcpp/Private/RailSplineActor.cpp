#include "RailSplineActor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

ARailSplineActor::ARailSplineActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create the spline component
    RailSpline = CreateDefaultSubobject<USplineComponent>("RailSpline");
    RootComponent = RailSpline;

    // Don’t try to load anything here – just assign in the editor.
}

void ARailSplineActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // destroy any old segments
    for (auto* Comp : SplineMeshes)
        if (Comp) Comp->DestroyComponent();
    SplineMeshes.Empty();

    if (!SegmentMesh) return;  // make sure you picked one in the editor!

    const int32 Num = RailSpline->GetNumberOfSplinePoints();
    for (int32 i = 0; i < Num - 1; ++i)
    {
        USplineMeshComponent* SMC = NewObject<USplineMeshComponent>(this);
        SMC->RegisterComponentWithWorld(GetWorld());
        SMC->AttachToComponent(RailSpline, FAttachmentTransformRules::KeepWorldTransform);

        // assign mesh + material
        SMC->SetStaticMesh(SegmentMesh);
        if (SegmentMaterial)
            SMC->SetMaterial(0, SegmentMaterial);

        // grab **world** positions & tangents
        const FVector StartPos = RailSpline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        const FVector StartTan = RailSpline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::World);
        const FVector EndPos = RailSpline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World);
        const FVector EndTan = RailSpline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::World);

        // **world**-space API
        SMC->SetStartPosition(StartPos, ESplineCoordinateSpace::World);
        SMC->SetStartTangent(StartTan, ESplineCoordinateSpace::World);
        SMC->SetEndPosition(EndPos, ESplineCoordinateSpace::World);
        SMC->SetEndTangent(EndTan, ESplineCoordinateSpace::World);

        SplineMeshes.Add(SMC);
    }
}
