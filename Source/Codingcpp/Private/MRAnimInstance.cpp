#include "MRAnimInstance.h"
#include "MRCharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"


void UMRAnimInstance::NativeInitializeAnimation()
{
    OwnerPawn = TryGetPawnOwner();
    if (OwnerPawn)
        MoveComp = Cast<UMRCharacterMovementComponent>(OwnerPawn->GetMovementComponent());
    LastRot = OwnerPawn ? OwnerPawn->GetActorRotation() : FRotator::ZeroRotator;
}

void UMRAnimInstance::NativeUpdateAnimation(float DT)
{
    if (!OwnerPawn) OwnerPawn = TryGetPawnOwner();
    if (!OwnerPawn) return;

    if (!MoveComp) MoveComp = Cast<UMRCharacterMovementComponent>(OwnerPawn->GetMovementComponent());

    /* ---- locomotion ---- */
    GroundSpeed = OwnerPawn->GetVelocity().Size2D();
    bIsInAir = MoveComp ? MoveComp->IsFalling() : false;
    Gait = MoveComp ? MoveComp->GetCurrentGait() : EGait::Walk;

    /* ---- rotate-in-place / lean ---- */
    const FRotator CurRot = OwnerPawn->GetActorRotation();
    const float DeltaYaw = UKismetMathLibrary::NormalizedDeltaRotator(CurRot, LastRot).Yaw;
    const float TargetYawPerSec = DeltaYaw / DT;

    // Smooth for nicer animation curves
    YawDelta = FMath::FInterpTo(YawDelta, TargetYawPerSec, DT, 6.f);
    Lean = FMath::Clamp(YawDelta / 360.f, -1.f, 1.f);

    LastRot = CurRot;
}
