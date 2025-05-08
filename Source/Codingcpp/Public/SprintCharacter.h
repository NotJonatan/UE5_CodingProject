// Source/Codingcpp/Public/SprintCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SprintCharacter.generated.h"
#include "InputActionValue.h"               // for FInputActionValue



class UInputAction;
class UInputMappingContext;

/** Simple character that can sprint when you hold the Sprint action. */
UCLASS()
class CODINGCPP_API ASprintCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASprintCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    // --- Enhanced Input Assets ---
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* IMC_Gameplay;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Move;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Look;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Jump;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Sprint;

    // --- Movement callbacks ---
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);

    // Sprint
    void StartSprinting(const FInputActionValue& Value);
    void StopSprinting(const FInputActionValue& Value);

    // Jump
    void JumpAction(const FInputActionValue& Value);

    // Speeds
    UPROPERTY(EditDefaultsOnly, Category = "Sprint")
    float WalkSpeed = 600.f;

    UPROPERTY(EditDefaultsOnly, Category = "Sprint")
    float SprintSpeed = 1200.f;
};