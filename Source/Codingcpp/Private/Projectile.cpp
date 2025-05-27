// Projectile.cpp
#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "Engine/World.h"

AProjectile::AProjectile()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    RootComponent = Mesh;
    Mesh->SetNotifyRigidBodyCollision(true);
    Mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

    Move = CreateDefaultSubobject<UProjectileMovementComponent>("Move");
    Move->InitialSpeed = 2200.f;
    Move->MaxSpeed = 2200.f;
    Move->bRotationFollowsVelocity = true;

    SetLifeSpan(3.f);
}

void AProjectile::OnHit(
    UPrimitiveComponent* HitComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector              NormalImpulse,
    const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
        if (UHealthComponent* HC = OtherActor->FindComponentByClass<UHealthComponent>())
            HC->TakeDamage(25.f);

    Destroy();
}
