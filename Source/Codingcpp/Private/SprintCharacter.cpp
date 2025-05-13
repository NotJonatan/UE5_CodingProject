// Source/Codingcpp/Private/SprintCharacter.cpp
//#include "Codingcpp.h"                             // causes error if this isn't first library
#include "SprintCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "InteractableInterface.h"
#include "GameFramework/PlayerController.h"

//DEFINE_LOG_CATEGORY(LogTemplateCharacter);


ASprintCharacter::ASprintCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Don’t rotate character to controller; let movement orient the mesh
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure movement to face input direction
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);

    // Movement defaults
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    // Camera boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.f;
    CameraBoom->bUsePawnControlRotation = true;

    // Follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    //GetMesh()->SetAnimClass(UGASAnimInstance::StaticClass());

    //// If you have a Blueprint anim BP called ABP_GameAnimSample, do this:
    //static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPClass(TEXT("/Game/Path/To/ABP_GameAnimSample"));
    //if (AnimBPClass.Succeeded())
    //{
    //    GetMesh()->SetAnimClass(AnimBPClass.Class);
    //}

    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}

void ASprintCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (ULocalPlayer* LP = PC->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsys = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
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
        
        //Interact

        PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ASprintCharacter::DoInteract);
    }
}

void ASprintCharacter::MoveInput(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        // get right vector 
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // add movement 
        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void ASprintCharacter::LookInput(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // add yaw and pitch input to controller
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void ASprintCharacter::StartSprinting(const FInputActionValue& /*Value*/)
{
    GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ASprintCharacter::StopSprinting(const FInputActionValue& /*Value*/)
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ASprintCharacter::DoInteract()
{
    FVector Start = FollowCamera->GetComponentLocation();
    FVector End = Start + (FollowCamera->GetForwardVector() * 300.f);
    FHitResult Hit;
    FCollisionQueryParams Params(NAME_None, false, this);

    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
    {
        AActor* HitActor = Hit.GetActor();
        if (HitActor && HitActor->GetClass()->ImplementsInterface
        (UInteractableInterface::StaticClass()))
        {
            // calls the blueprint/native implementation
            IInteractableInterface::Execute_Interact(HitActor, this);
        }
    }
}