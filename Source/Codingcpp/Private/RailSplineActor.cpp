// RailSplineActor.cpp

#include "RailSplineActor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

ARailSplineActor::ARailSplineActor()
{
    PrimaryActorTick.bCanEverTick = false;

    RailSpline = CreateDefaultSubobject<USplineComponent>(TEXT("RailSpline"));
    RootComponent = RailSpline;
}

void ARailSplineActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // Clear out old spline meshes
    for (USplineMeshComponent* Comp : SplineMeshes)
    {
        if (Comp)
        {
            Comp->DestroyComponent();
        }
    }
    SplineMeshes.Empty();

    if (!SegmentMesh) return;

    const int32 NumPoints = RailSpline->GetNumberOfSplinePoints();

    for (int32 i = 0; i < NumPoints - 1; ++i)
    {
        // Create new spline‐mesh component
        USplineMeshComponent* SMC = NewObject<USplineMeshComponent>(this);
        SMC->RegisterComponentWithWorld(GetWorld());
        SMC->AttachToComponent(RailSpline, FAttachmentTransformRules::KeepRelativeTransform);
        SMC->SetMobility(EComponentMobility::Movable);

        // Assign mesh + optional material
        SMC->SetStaticMesh(SegmentMesh);
        if (SegmentMaterial)
        {
            SMC->SetMaterial(0, SegmentMaterial);
        }

        // Basic blocking collision
        SMC->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        SMC->SetCollisionProfileName(TEXT("BlockAll"));
        SMC->SetGenerateOverlapEvents(false);

        // Deform along the spline in world space
        const FVector StartPos = RailSpline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        const FVector StartTan = RailSpline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::World);
        const FVector EndPos = RailSpline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World);
        const FVector EndTan = RailSpline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::World);

        SMC->SetStartPosition(StartPos, ESplineCoordinateSpace::World);
        SMC->SetStartTangent(StartTan, ESplineCoordinateSpace::World);
        SMC->SetEndPosition(EndPos, ESplineCoordinateSpace::World);
        SMC->SetEndTangent(EndTan, ESplineCoordinateSpace::World);

        // Track for cleanup
        SplineMeshes.Add(SMC);
    }
}
