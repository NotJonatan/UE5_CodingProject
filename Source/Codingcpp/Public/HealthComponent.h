#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// Delegate for broadcasting health changes: (NewHealth, Delta)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, NewHealth, float, HealthDelta);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CODINGCPP_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHealthComponent();

    /** Maximum health (settable in BP or here) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth = 100.f;

    /** Current health — read‐only in BP */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    float CurrentHealth;

    /** Fires on any change to CurrentHealth */
    UPROPERTY(BlueprintAssignable, Category = "Health")
    FOnHealthChangedSignature OnHealthChanged;

    /** Deal damage to this component (clamped ≥0) */
    UFUNCTION(BlueprintCallable, Category = "Health")
    void TakeDamage(float DamageAmount);

    /** Heal this component (clamped ≤MaxHealth) */
    UFUNCTION(BlueprintCallable, Category = "Health")
    void Heal(float HealAmount);

protected:
    virtual void BeginPlay() override;

private:
    /** Handler for the owning actor’s OnTakeAnyDamage event */
    UFUNCTION()
    void HandleTakeAnyDamage(AActor* DamagedActor, float Damage,
        const UDamageType* DamageType,
        AController* InstigatedBy,
        AActor* DamageCauser);
};
