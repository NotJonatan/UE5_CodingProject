// Source/Codingcpp/Public/SprintCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// Enhanced Input
#include "InputActionValue.h"            // <<–– for FInputActionValue
#include "InputMappingContext.h"
#include "InputAction.h"

//#include "EnhancedInputComponent.h"
//#include "EnhancedInputSubsystems.h"


class UInputMappingContext;
class UInputAction;

#include "SprintCharacter.generated.h"

UCLASS()
class CODINGCPP_API ASprintCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASprintCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    //–– Input callbacks ––
    void MoveInput(const FInputActionValue& Value);
    void LookInput(const FInputActionValue& Value);
    void StartSprinting(const FInputActionValue& Value);
    void StopSprinting(const FInputActionValue& Value);

    //–– Sprint speeds ––
    UPROPERTY(EditDefaultsOnly, Category = "Sprint")
    float WalkSpeed = 600.f;

    UPROPERTY(EditDefaultsOnly, Category = "Sprint")
    float SprintSpeed = 1200.f;

    //–– Enhanced Input assets (assign in BP) ––
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Move;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Look;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Jump;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Sprint;
};