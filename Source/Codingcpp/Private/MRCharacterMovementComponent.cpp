// Fill out your copyright notice in the Description page of Project Settings.


#include "MRCharacterMovementComponent.h"

// Sets default values for this component's properties
UMRCharacterMovementComponent::UMRCharacterMovementComponent()
{
		// Make sure replication is on for multiplayer later
	SetIsReplicatedByDefault(true);

}


void UMRCharacterMovementComponent::OnMovementUpdated(float Delta, const FVector&, const FVector&)
{
    Super::OnMovementUpdated(Delta, {}, {});
    EvaluateGait();
}

void UMRCharacterMovementComponent::EvaluateGait()
{
    const float Speed = Velocity.Size2D();
    EGait NewGait = (Speed > 650.f) ? EGait::Sprint
        : (Speed > 325.f) ? EGait::Run
        : EGait::Walk;

    if (NewGait != CurrentGait)
    {
        CurrentGait = NewGait;
        OnGaitChanged.Broadcast(CurrentGait);
    }
}

void UMRCharacterMovementComponent::OnMovementModeChanged(EMovementMode Prev, uint8 PrevCustom)
{
    Super::OnMovementModeChanged(Prev, PrevCustom);

    // Example place to fire a “JustLanded” anim notify:
    if (Prev == MOVE_Falling && MovementMode == MOVE_Walking)
    {
        // Landed – could set a bool for one frame or raise another delegate
    }
}
