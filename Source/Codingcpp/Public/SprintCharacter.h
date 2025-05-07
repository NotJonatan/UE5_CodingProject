// Source/Codingcpp/Public/SprintCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SprintCharacter.generated.h"

/** Simple character that can sprint when you hold the Sprint action. */
UCLASS()
class CODINGCPP_API ASprintCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASprintCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Called on IE_Pressed for our Sprint action
    void StartSprinting();
    // Called on IE_Released
    void StopSprinting();

    // How fast we walk normally
    UPROPERTY(EditDefaultsOnly, Category = "Sprint")
    float WalkSpeed = 600.f;

    // How fast we go when sprinting
    UPROPERTY(EditDefaultsOnly, Category = "Sprint")
    float SprintSpeed = 1200.f;
};
