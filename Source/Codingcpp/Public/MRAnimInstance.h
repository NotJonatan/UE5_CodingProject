// Source/Codingcpp/Public/MRAnimInstance.h
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MRAnimInstance.generated.h"

// forward decls so the pointers compile
class APawn;
class UCharacterMovementComponent;

UCLASS()
class CODINGCPP_API UMRAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
    // speed along the ground
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
    float Speed = 0.f;

    // movement direction in degrees
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
    float Direction = 0.f;

    // are we currently in the air?
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
    bool bIsInAir = false;

private:
    // cache the pawn & its movement component
    APawn* PawnOwner = nullptr;
    UCharacterMovementComponent* MoveComp = nullptr;
};
