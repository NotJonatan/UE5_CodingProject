// Source/Codingcpp/Public/SprintCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// Enhanced Input
#include "InputActionValue.h"            // <<–– for FInputActionValue
#include "InputMappingContext.h"
#include "InputAction.h"

#include "Engine/World.h"             // for UWorld, GetWorld()
#include "GameFramework/WorldSettings.h" // for AWorldSettings
#include "TimerManager.h"             // for FTimerManager
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
class AWorldSettings;

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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Interact;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* IA_Fire;

    // Sprint speeds
    UPROPERTY(EditDefaultsOnly, Category = "Sprint")
    float WalkSpeed = 300.f;
    UPROPERTY(EditDefaultsOnly, Category = "Sprint")
    float SprintSpeed = 600.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MR|Movement", meta = (AllowPrivateAccess = "true"))
    UMRCharacterMovementComponent * MRMovement = nullptr;
    
           /* Design-time speeds in one place */
    UPROPERTY(EditDefaultsOnly, Category = "MR|Movement")
    FMRMovementSettings MovementSettings;

    //AUploadStationActor* StationInRange = nullptr;

    // in your character class body:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
    UHealthComponent* HealthComponent;

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    //UShooterComponent* Shooter;
    public:

        /** Activates the one‐time sandevistan effect */
    UFUNCTION(BlueprintCallable, Category = "Sandevistan")
    void ActivateSandevistan();

    // Internal helper to restore normal time
    UFUNCTION()
    void ResetTimeDilation();

    /** How long the slowdown lasts (seconds) */
    UPROPERTY(EditAnywhere, Category = "Sandevistan")
    float SandevistanDuration = 3.f;

    /** Cooldown before you can use it again */
    UPROPERTY(EditAnywhere, Category = "Sandevistan")
    float SandevistanCooldown = 10.f;

    // Track whether it’s already active
    bool bIsSandevistanActive = false;

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


    ASprintCharacter(const FObjectInitializer& ObjectInitializer);

    // Expose camera components
    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

    /** Handle for our timer */
    FTimerHandle SandevistanTimerHandle;
};