#include "ZiplineActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"

AZiplineActor::AZiplineActor()
{
    PrimaryActorTick.bCanEverTick = true;

    Cable = CreateDefaultSubobject<UStaticMeshComponent>("Cable");
    RootComponent = Cable;                            // OK: UStaticMeshComponent → USceneComponent*

    Trigger = CreateDefaultSubobject<UBoxComponent>("Trigger");
    Trigger->SetupAttachment(RootComponent);
    Trigger->SetBoxExtent(FVector(60.f));
    Trigger->SetCollisionProfileName(TEXT("Trigger"));

    Trigger->OnComponentBeginOverlap.AddDynamic(
        this, &AZiplineActor::BeginOverlap);
}

void AZiplineActor::BeginOverlap(UPrimitiveComponent*, AActor* Other,
    UPrimitiveComponent*, int32, bool, const FHitResult&)
{
    if (RidingChar) return;

    ACharacter* C = Cast<ACharacter>(Other);
    if (!C) return;

    RidingChar = C;
    Progress = 0.f;

    C->GetCharacterMovement()->DisableMovement();
    C->SetActorLocation(GetPoint(0.f));
}

void AZiplineActor::Tick(float Dt)
{
    Super::Tick(Dt);
    if (!RidingChar) return;

    const float Len = FVector::Distance(LineStart, LineEnd);
    Progress += (SlideSpeed * Dt) / Len;

    if (Progress >= 1.f)
    {
        RidingChar->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
        RidingChar = nullptr;
        return;
    }

    FVector P = GetPoint(Progress);
    FRotator R = (LineEnd - LineStart).Rotation();
    RidingChar->SetActorLocationAndRotation(P, R);
}
