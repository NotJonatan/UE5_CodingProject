// Source/Codingcpp/Private/SprintCharacter.cpp
#include "SprintCharacter.h"
//#include "Codingcpp.h"                             // causes error if this isn't first library
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"

#define SPRINT_ACTION_NAME "Sprint"

ASprintCharacter::ASprintCharacter()
{
    // ensure our movement component starts at WalkSpeed
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ASprintCharacter::BeginPlay()
{
    Super::BeginPlay();
    // in case someone tweaked WalkSpeed in the editor
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ASprintCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // bind sprint pressed/released
    PlayerInputComponent->BindAction(SPRINT_ACTION_NAME, IE_Pressed, this, &ASprintCharacter::StartSprinting);
    PlayerInputComponent->BindAction(SPRINT_ACTION_NAME, IE_Released, this, &ASprintCharacter::StopSprinting);

    // TODO: bind MoveForward/MoveRight axes here
}

void ASprintCharacter::StartSprinting()
{
    GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ASprintCharacter::StopSprinting()
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
