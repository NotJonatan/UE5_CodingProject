// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MRMovementTypes.generated.h"


/** High-level gait used by the locomotion blend-space */
UENUM(BlueprintType)
enum class EGait : uint8
{
    Walk    UMETA(DisplayName = "Walk"),
    Run     UMETA(DisplayName = "Run"),
    Sprint  UMETA(DisplayName = "Sprint")
};

/** Design-time tuning container (can live on the Character BP) */
USTRUCT(BlueprintType)
struct FMRMovementSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly) float WalkSpeed = 300.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) float RunSpeed = 550.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly) float SprintSpeed = 750.f;
};