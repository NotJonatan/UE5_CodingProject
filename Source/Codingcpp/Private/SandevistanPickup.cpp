#include "SandevistanPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "InventoryComponent.h"

ASandevistanPickup::ASandevistanPickup()
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

void ASandevistanPickup::BeginPlay()
{
    Super::BeginPlay();
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASandevistanPickup::OnOverlap);
}

void ASandevistanPickup::OnOverlap(
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
        if (UInventoryComponent* Inv = Char->FindComponentByClass<UInventoryComponent>())
        {
            Inv->AddSandevistanCharge();
            Destroy();
        }
    }
}
