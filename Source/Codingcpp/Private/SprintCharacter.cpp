// Source/Codingcpp/Private/SprintCharacter.cpp
//#include "Codingcpp.h"                             // causes error if this isn't first library
#include "SprintCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"    // <-- correct subsystem header
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/LocalPlayer.h"        // <–– for ULocalPlayer


ASprintCharacter::ASprintCharacter()
{
    // CharacterMovement defaults
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ASprintCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Add our mapping context so Enhanced Input knows about it
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsys =
                LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                Subsys->AddMappingContext(DefaultMappingContext, 0);
            }
        }
    }
}

void ASprintCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Movement & Look
        EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ASprintCharacter::MoveInput);
        EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ASprintCharacter::LookInput);

        // Jump
        EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
        EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        // Sprint
        EIC->BindAction(IA_Sprint, ETriggerEvent::Started, this, &ASprintCharacter::StartSprinting);
        EIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ASprintCharacter::StopSprinting);
    }
}
void ASprintCharacter::MoveInput(const FInputActionValue& Value)
{
    const FVector2D Delta = Value.Get<FVector2D>();
    AddMovementInput(GetActorForwardVector(), Delta.Y);
    AddMovementInput(GetActorRightVector(), Delta.X);
}


void ASprintCharacter::LookInput(const FInputActionValue& Value)
{
    const FVector2D Delta = Value.Get<FVector2D>();
    AddControllerYawInput(Delta.X);
    AddControllerPitchInput(Delta.Y);
}

void ASprintCharacter::StartSprinting(const FInputActionValue& Value)
{
    GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ASprintCharacter::StopSprinting(const FInputActionValue& Value)
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}