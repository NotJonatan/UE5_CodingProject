#include "HealthPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"

AHealthPickup::AHealthPickup()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComp = CreateDefaultSubobject<USphereComponent>("CollisionComp");
    CollisionComp->InitSphereRadius(75.f);
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    RootComponent = CollisionComp;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
    MeshComp->SetupAttachment(RootComponent);
}

void AHealthPickup::BeginPlay()
{
    Super::BeginPlay();
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::OnOverlap);
}

void AHealthPickup::OnOverlap(
    UPrimitiveComponent* /*Overlapped*/,
    AActor* OtherActor,
    UPrimitiveComponent* /*OtherComp*/,
    int32 /*OtherBodyIndex*/,
    bool /*bFromSweep*/,
    const FHitResult& /*Sweep*/
)
{
    if (ACharacter* Char = Cast<ACharacter>(OtherActor))
    {
        if (UHealthComponent* HC = Char->FindComponentByClass<UHealthComponent>())
        {
            HC->Heal(HealAmount);
            Destroy();
        }
    }
}
