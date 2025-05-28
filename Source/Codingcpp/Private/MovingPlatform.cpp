#include "MovingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/DamageType.h"             // your chosen damage type header

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;

    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlatformMesh");
    RootComponent = PlatformMesh;

    // enable overlap events
    SetActorEnableCollision(true);
    OnActorBeginOverlap.AddDynamic(this, &AMovingPlatform::OnPlatformOverlap);
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    // capture world-space start, and interpret PointB as an offset
    PointA = GetActorLocation();
    PointB = PointA + PointB;
    CurrentTarget = PointB;
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector NewLocation = FMath::VInterpConstantTo(
        GetActorLocation(),
        CurrentTarget,
        DeltaTime,
        MoveSpeed
    );
    SetActorLocation(NewLocation);

    SwapTargetIfNeeded();
}

void AMovingPlatform::SwapTargetIfNeeded()
{
    if (FVector::DistSquared(GetActorLocation(), CurrentTarget) < FMath::Square(10.f))
    {
        CurrentTarget = (CurrentTarget == PointA) ? PointB : PointA;
    }
}

void AMovingPlatform::OnPlatformOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (ACharacter* Char = Cast<ACharacter>(OtherActor))
    {
        // apply damage once per overlap
        UGameplayStatics::ApplyDamage(
            Char,
            DamageAmount,
            nullptr,            // instigator
            this,               // damage causer
            DamageType
        );
    }
}
