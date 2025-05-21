// Source/Codingcpp/Public/SprintCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// Enhanced Input
#include "InputActionValue.h"            // <<–– for FInputActionValue
#include "InputMappingContext.h"
#include "InputAction.h"


#include "InventoryComponent.h"
#include "HealthComponent.h"        // at the top
#include "InteractableInterface.h"
#include "MRMovementTypes.h"               // <-- add
#include "MRCharacterMovementComponent.h"  // <-- add
#include "SprintCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS(config = Game)
class CODINGCPP_API ASprintCharacter : public ACharacter
{
    GENERATED_BODY()

    /* Inventory component the player carries around */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
    UInventoryComponent* Inventory;

    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;

    // Enhanced Input assets (assign these in your SprintCharacter BP)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* DefaultMappingContext;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Move;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Look;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Jump;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Sprint;

    // Sprint speeds
    UPROPERTY(EditDefaultsOnly, Category = "Sprint")
    float WalkSpeed = 600.f;
    UPROPERTY(EditDefaultsOnly, Category = "Sprint")
    float SprintSpeed = 1200.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MR|Movement", meta = (AllowPrivateAccess = "true"))
    UMRCharacterMovementComponent * MRMovement = nullptr;
    
           /* Design-time speeds in one place */
    UPROPERTY(EditDefaultsOnly, Category = "MR|Movement")
    FMRMovementSettings MovementSettings;

//private:
    // in your character class body:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
    UHealthComponent* HealthComponent;

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    // Input callbacks
    void MoveInput(const FInputActionValue& Value);
    void LookInput(const FInputActionValue& Value);
    void StartSprinting(const FInputActionValue& Value);
    void StopSprinting(const FInputActionValue& Value);

    /** Called when player presses Interact */
    void DoInteract();

public:
    ASprintCharacter(const FObjectInitializer& ObjectInitializer);

    // Expose camera components
    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};