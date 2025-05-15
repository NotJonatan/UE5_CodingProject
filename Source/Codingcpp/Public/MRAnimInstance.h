#pragma once
#include "CoreMinimal.h"                     // 1️⃣  always first
#include "Animation/AnimInstance.h"          // 2️⃣  base-class header
#include "MRMovementTypes.h"                 //     (for EGait enum)
#include "MRAnimInstance.generated.h"        // 3️⃣  always last

class UMRCharacterMovementComponent;

UCLASS()
class CODINGCPP_API UMRAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    /* ---- Read-only to the AnimGraph ---- */
    UPROPERTY(BlueprintReadOnly, Category = "MR|Anim") float GroundSpeed = 0.f;
    UPROPERTY(BlueprintReadOnly, Category = "MR|Anim") bool  bIsInAir = false;
    UPROPERTY(BlueprintReadOnly, Category = "MR|Anim") float YawDelta = 0.f;   // deg / sec
    UPROPERTY(BlueprintReadOnly, Category = "MR|Anim") float Lean = 0.f;   // -1↔1
    UPROPERTY(BlueprintReadOnly, Category = "MR|Anim") EGait Gait = EGait::Walk;

private:
    // cached
    APawn* OwnerPawn = nullptr;
    UMRCharacterMovementComponent* MoveComp = nullptr;
    FRotator LastRot = FRotator::ZeroRotator;
};
