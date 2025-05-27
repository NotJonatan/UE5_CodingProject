#include "HealthComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "MidnightRushGameMode.h"

UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    // Initialize health
    CurrentHealth = MaxHealth;

    // Bind to the owner’s damage event
    if (AActor* Owner = GetOwner())
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeAnyDamage);
    }
}

void UHealthComponent::HandleTakeAnyDamage(AActor* /*DamagedActor*/, float Damage,
    const UDamageType* /*DamageType*/,
    AController* /*InstigatedBy*/,
    AActor* /*DamageCauser*/)
{
    if (Damage <= 0.f || CurrentHealth <= 0.f)
    {
        return;
    }
    TakeDamage(Damage);
}

void UHealthComponent::TakeDamage(float DamageAmount)
{
    const float Old = CurrentHealth;
    CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);
    const float Delta = CurrentHealth - Old;
    OnHealthChanged.Broadcast(CurrentHealth, Delta);

    /* ─── death check ─── */
    if (CurrentHealth <= 0.f)
    {
        if (AActor* Owner = GetOwner())
        {
            if (AMidnightRushGameMode* GM =
                Owner->GetWorld()->GetAuthGameMode<AMidnightRushGameMode>())
            {
                GM->NotifyPlayerDied();
            }

            Owner->Destroy();
        }
    }
}
void UHealthComponent::Heal(float HealAmount)
{
    const float OldHealth = CurrentHealth;
    CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.f, MaxHealth);
    const float Delta = CurrentHealth - OldHealth;
    OnHealthChanged.Broadcast(CurrentHealth, Delta);
}
