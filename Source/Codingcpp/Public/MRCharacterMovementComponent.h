// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MRMovementTypes.h"
#include "MRCharacterMovementComponent.generated.h"

/* ----- delegate BEFORE it’s referenced ----- */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGaitChanged, EGait, NewGait);


UCLASS( ClassGroup=(Movement), meta=(BlueprintSpawnableComponent) )
class CODINGCPP_API UMRCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMRCharacterMovementComponent();
	// Core hook every tick
	virtual void OnMovementUpdated(float DeltaTime,
		const FVector& OldLocation,
		const FVector& OldVelocity) override;


	// Detect jump → land
	virtual void OnMovementModeChanged(EMovementMode Prev, uint8 PrevCustom) override;

	/** Current allowed gait (speed-based) */
	UFUNCTION(BlueprintPure, Category = "MR|Movement")
	EGait GetCurrentGait() const { return CurrentGait; }

	/** Broadcast when the gait flips (walk→run→sprint) */
	UPROPERTY(BlueprintAssignable, Category = "MR|Movement")
	FOnGaitChanged OnGaitChanged;


protected:
	/** Speed → gait rules */
	void EvaluateGait();

	EGait CurrentGait = EGait::Walk;
};