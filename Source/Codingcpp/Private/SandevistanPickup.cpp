// Source/Codingcpp/Private/SandevistanPickup.cpp

#include "SandevistanPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "InventoryComponent.h"
#include "Engine/Engine.h"               // for GEngine
#include "Kismet/GameplayStatics.h"      // for UGameplayStatics
#include "GameFramework/Character.h"     // for ASprintCharacter cast
#include "SprintCharacter.h"             // for ActivateSandevistan() call


ASandevistanPickup::ASandevistanPickup()
{
    PrimaryActorTick.bCanEverTick = false;
    // collision
    CollisionComp = CreateDefaultSubobject<USphereComponent>("CollisionComp");
    CollisionComp->InitSphereRadius(75.f);
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    CollisionComp->SetGenerateOverlapEvents(true);                  // <— make sure overlaps are enabled
    //CollisionComp->OnComponentBeginOverlap.AddDynamic(              // this only works if we are only using the Onoverlap collsion. 
        //this, &ASandevistanPickup::OnOverlap);


    RootComponent = CollisionComp;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
    MeshComp->SetupAttachment(RootComponent);
}

void ASandevistanPickup::BeginPlay()
{
    Super::BeginPlay();


}


void ASandevistanPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1, 2.f, FColor::Yellow,
            TEXT("Sandevistan ready to be used for 1 time!"));
    }
    if (ASprintCharacter* PC = Cast<ASprintCharacter>(OtherActor))
    {
        if (UInventoryComponent* Inv = PC->FindComponentByClass<UInventoryComponent>())
        {
            Inv->AddSandevistanCharge();
            Destroy();  // remove the pickup
        }
    }
}