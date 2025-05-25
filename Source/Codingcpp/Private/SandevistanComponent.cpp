// SandevistanComponent.cpp
#include "SandevistanComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

USandevistanComponent::USandevistanComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    // Create the Niagara Component up-front
    VFXComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SandevistanVFX"));
    VFXComponent->SetupAttachment(GetOwner()->GetRootComponent());
    VFXComponent->SetAutoActivate(false);
}

void USandevistanComponent::BeginPlay()
{
    Super::BeginPlay();

    // If you've assigned the system in the editor, push it into the component now
    if (VFXSystem && VFXComponent)
    {
        VFXComponent->SetAsset(VFXSystem);
    }
}

void USandevistanComponent::ActivateSandevistan(float Duration)
{
	if (VFXComponent && !VFXComponent->IsActive())
	{
		VFXComponent->Activate(true);

		// Optionally schedule deactivation after Duration:
		FTimerHandle UnusedHandle;
		GetWorld()->GetTimerManager().SetTimer(
			UnusedHandle,
			[this]() { VFXComponent->Deactivate(); },
			Duration,
			false
		);
	}
}