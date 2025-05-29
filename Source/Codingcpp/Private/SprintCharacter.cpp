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
#include "MRCharacterMovementComponent.h"    // add
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h" // Debug
#include "TimerManager.h"

//DEFINE_LOG_CATEGORY(LogTemplateCharacter);


ASprintCharacter::ASprintCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UMRCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{

    MRMovement = Cast<UMRCharacterMovementComponent>(GetCharacterMovement());
    MRMovement->RotationRate = FRotator(0.f, 540.f, 0.f);
    MRMovement->JumpZVelocity = 700.f;
    MRMovement->MaxWalkSpeed = MovementSettings.RunSpeed;
    MRMovement->BrakingDecelerationWalking = 2048.f;

    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Don’t rotate character to controller; let movement orient the mesh
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure movement to face input direction
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);

    //// Movement defaults Hotkeys - CTRL + K + C OR CTRL + K and again CTRL + C. Undo with CTROL + K and CTRL + U
    //GetCharacterMovement()->JumpZVelocity = 700.f;
    //GetCharacterMovement()->AirControl = 0.35f;
    //GetCharacterMovement()->MaxWalkSpeed = 500.f;
    //GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    //GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    //GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

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

    //HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

    Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

    //Shooter = CreateDefaultSubobject<UShooterComponent>("Shooter");

        // Expose a respawn point reference
    SpawnPosition = nullptr;


}

void ASprintCharacter::BeginPlay()
{
    Super::BeginPlay();
    MRMovement = Cast<UMRCharacterMovementComponent>(GetCharacterMovement());
    check(MRMovement);

    // Cache default speeds for later scaling
    DefaultWalkSpeed = WalkSpeed;
    DefaultSprintSpeed = SprintSpeed;

    bIsSandevistanActive = false;

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
        EIC->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &ASprintCharacter::DoInteract);
        // add this once, right after the bind so we know it’s configured
        UE_LOG(LogTemp, Log, TEXT("[Input] IA_Interact is pressed"));

        // Bind Sandevistan Action
        EIC->BindAction(IA_Sandevistan, ETriggerEvent::Triggered, this, &ASprintCharacter::OnSandevistan);

        // Bind Respawn Action
        EIC->BindAction(IA_Respawn, ETriggerEvent::Triggered, this, &ASprintCharacter::OnRespawn);
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
    /* ---------- sanity checks ---------- */
    if (!FollowCamera)          return;              // camera missing – nothing to do
    if (!GetWorld())            return;

    /* ---------- line-trace in front of the camera ---------- */
    const FVector  Start = FollowCamera->GetComponentLocation();
    const FVector  End = Start + FollowCamera->GetForwardVector() * 1000.f;

    DrawDebugSphere(GetWorld(), End, 8.f, 8,
        FColor::Red, false, 2.f);   // shows the end-point

    FHitResult            Hit;
    FCollisionQueryParams Params(NAME_None, /*bTraceComplex=*/false, this);

    const bool bHit = GetWorld()->LineTraceSingleByChannel(
        Hit, Start, End, ECC_Visibility, Params);

    if (bHit)
    {
        if (AActor* HitActor = Hit.GetActor())
        {
            if (HitActor->GetClass()->ImplementsInterface(
                UInteractableInterface::StaticClass()))
            {
                IInteractableInterface::Execute_Interact(HitActor, this);
            }
        }
    }

    /* ---------- fallback: standing in an UploadStation trigger ---------- */
    if (Inventory && Inventory->bInUploadRange)
    {
        const int32 Num = Inventory->UploadAllDrives();
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1, 2.f, FColor::Yellow,
                FString::Printf(TEXT("Uploaded %d drive(s)!"), Num));
        }
    }

    /* ---------- debug: what did we hit? ---------- */
    const FString NameStr = bHit && Hit.GetActor()
        ? Hit.GetActor()->GetName()
        : TEXT("None");
    UE_LOG(LogTemp, Log, TEXT("[Interact] trace result: %s"), *NameStr);
}

void ASprintCharacter::ActivateSandevistan()
{
    if (bIsSandevistanActive) return;
    bIsSandevistanActive = true;

    UWorld* World = GetWorld();
    if (!World) return;

    // 1) Slow the world
    const float SlowAmount = 0.2f;
    UGameplayStatics::SetGlobalTimeDilation(World, SlowAmount);

    // 2) Counteract on the player: tick & anim only
    const float Inverse = 1.f / SlowAmount;
    CustomTimeDilation = Inverse;
    if (GetMesh())
    {
        GetMesh()->GlobalAnimRateScale = Inverse;
    }

    // 3) Play VFX
    if (SandevistanVFXComponent)
    {
        SandevistanVFXComponent->Activate(true);
    }

    // 4) Schedule reset
    World->GetTimerManager().SetTimer(
        SandevistanTimerHandle,
        this,
        &ASprintCharacter::ResetTimeDilation,
        SandevistanDuration,
        false
    );
}

void ASprintCharacter::ResetTimeDilation()
{
    UWorld* World = GetWorld();
    if (World)
    {
        UGameplayStatics::SetGlobalTimeDilation(World, 1.f);
    }

    // Restore actor tick & anim
    CustomTimeDilation = 1.f;
    if (GetMesh())
    {
        GetMesh()->GlobalAnimRateScale = 1.f;
    }

    // Turn VFX off
    if (SandevistanVFXComponent)
    {
        SandevistanVFXComponent->Deactivate();
    }

    bIsSandevistanActive = false;
}

// Respawn logic implementation
void ASprintCharacter::OnRespawn()
{
    if (SpawnPosition)
    {
        SetActorLocation(SpawnPosition->GetActorLocation());
        SetActorRotation(SpawnPosition->GetActorRotation());
        UE_LOG(LogTemp, Warning, TEXT("Player Respawned!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("SpawnPosition is not set! Please assign it in the editor."));
    }
}

void ASprintCharacter::OnSandevistan()
{
    // Try to consume one charge
    if (Inventory && Inventory->ConsumeSandevistanCharge())
    {
        ActivateSandevistan();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No Sandevistan charges available!"));
        // Optionally: play “no ammo” sound or UI flash
    }
}