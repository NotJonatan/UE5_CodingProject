// SandevistanComponent.cpp
#include "SandevistanComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

USandevistanComponent::USandevistanComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USandevistanComponent::BeginPlay()
{
    Super::BeginPlay();

    // If you've assigned the system in the editor, create & configure the runtime Niagara component now:
	if (VFXSystem)
	{
		// Create the NiagaraComponent as a child of the owner
		VFXComponent = NewObject<UNiagaraComponent>(GetOwner(), TEXT("SandevistanVFX"));
		VFXComponent->SetupAttachment(GetOwner()->GetRootComponent());
		VFXComponent->SetAsset(VFXSystem);
		VFXComponent->bAutoActivate = false;
		VFXComponent->RegisterComponent();
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