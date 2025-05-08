// Source/Codingcpp/Private/SprintCharacter.cpp
#include "SprintCharacter.h"
//#include "Codingcpp.h"                             // causes error if this isn't first library
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Components/InputComponent.h"

//#define SPRINT_ACTION_NAME "Sprint"

ASprintCharacter::ASprintCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ASprintCharacter::BeginPlay()
{
    Super::BeginPlay();
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ASprintCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ASprintCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASprintCharacter::MoveRight);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASprintCharacter::StartSprinting);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASprintCharacter::StopSprinting);
    // ...etc
}

void ASprintCharacter::MoveForward(float Value)
{
    if (Value != 0.f)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void ASprintCharacter::MoveRight(float Value)
{
    if (Value != 0.f)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void ASprintCharacter::StartSprinting()
{
    GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ASprintCharacter::StopSprinting()
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}