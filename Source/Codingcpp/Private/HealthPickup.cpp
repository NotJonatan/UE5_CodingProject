// Source/Codingcpp/Private/HealthPickup.cpp

#include "HealthPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "Engine/Engine.h"                // << add this
#include "InventoryComponent.h"

AHealthPickup::AHealthPickup()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComp = CreateDefaultSubobject<USphereComponent>("CollisionComp");
    CollisionComp->InitSphereRadius(75.f);
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    CollisionComp->SetGenerateOverlapEvents(true);                  // <— make sure overlaps are enabled
    CollisionComp->OnComponentBeginOverlap.AddDynamic(
        this, &AHealthPickup::OnOverlap);                           // <— bind your OnOverlap

    RootComponent = CollisionComp;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
    MeshComp->SetupAttachment(RootComponent);
}

void AHealthPickup::BeginPlay()
{
    Super::BeginPlay();

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
    if (GEngine)
    {
        // print to screen for 2 seconds in green
        GEngine->AddOnScreenDebugMessage(
            -1, 2.f, FColor::Green,
            TEXT("Health restored by 50!!"));
    }

    if (ACharacter* Char = Cast<ACharacter>(OtherActor))
    {
        if (UHealthComponent* HC = Char->FindComponentByClass<UHealthComponent>())
        {
            HC->Heal(HealAmount);
            Destroy();
        }
    }
}
