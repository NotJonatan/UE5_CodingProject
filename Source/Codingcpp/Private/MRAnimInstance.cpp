// Source/Codingcpp/Private/MRAnimInstance.cpp
#include "MRAnimInstance.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMRAnimInstance::NativeInitializeAnimation()
{
    PawnOwner = TryGetPawnOwner();
    if (PawnOwner)
    {
        MoveComp = PawnOwner->FindComponentByClass<UCharacterMovementComponent>();
    }
}

void UMRAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    // if we haven’t cached yet, try again
    if (!PawnOwner)
    {
        PawnOwner = TryGetPawnOwner();
    }
    if (!MoveComp && PawnOwner)
    {
        MoveComp = PawnOwner->FindComponentByClass<UCharacterMovementComponent>();
    }

    if (!PawnOwner || !MoveComp)
    {
        return;
    }

    // horizontal speed
    FVector Vel = PawnOwner->GetVelocity();
    Vel.Z = 0.f;
    Speed = Vel.Size();

    // in-air?
    bIsInAir = MoveComp->IsFalling();

    // direction relative to facing
    Direction = CalculateDirection(Vel, PawnOwner->GetActorRotation());
}
