// Fill out your copyright notice in the Description page of Project Settings.
#include "SandevistanComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Camera/PlayerCameraManager.h"

// Sets default values for this component's properties
USandevistanComponent::USandevistanComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USandevistanComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



void USandevistanComponent::ActivateSandevistan(float Duration)
{
	if (!GetOwner() || !SandevistanFX) return;

	SpawnOrEnableFX();

	/** Optional camera overlay (single-player) */
	if (OverlayMaterial)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetOwner()->GetInstigatorController()))
		{
			PC->PlayerCameraManager->AddCameraFade(0.f, 0.f); // ensure fade layer exists
			PC->PlayerCameraManager->AddCachedPPMaterial(0, OverlayMaterial);
		}
	}

	/* Auto-deactivate after Duration seconds */
	if (Duration > 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_Deactivate, this, &USandevistanComponent::DeactivateSandevistan,
			Duration, /*bLoop=*/false);
	}
}

void USandevistanComponent::DeactivateSandevistan()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Deactivate);
	HideFX();

	/* Remove overlay */
	if (OverlayMaterial)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetOwner()->GetInstigatorController()))
		{
			PC->PlayerCameraManager->RemoveCachedPPMaterial(OverlayMaterial);
		}
	}
}

void USandevistanComponent::SpawnOrEnableFX()
{
	if (!FXComp)
	{
		/* Attach to mesh (for 3P) or to camera (for 1P) –
		   here we pick Owner’s root; tweak as needed. */
		FXComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			SandevistanFX,
			GetOwner()->GetRootComponent(),
			NAME_None,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::SnapToTarget,
			false  /* bAutoDestroy */
		);
	}
	else
	{
		FXComp->Activate(true);
	}
}

void USandevistanComponent::HideFX()
{
	if (FXComp)
	{
		FXComp->Deactivate();          // keeps the component, stops emission
	}
}