// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "SandevistanComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODINGCPP_API USandevistanComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USandevistanComponent();


public:	

	/** Call from input, ability, etc. */
	UFUNCTION(BlueprintCallable)
	void ActivateSandevistan(float Duration = 5.f);

	UFUNCTION(BlueprintCallable)
	void DeactivateSandevistan();

protected:
	virtual void BeginPlay() override;

	/** Asset you pick in the Details panel (a Niagara System) */
	UPROPERTY(EditDefaultsOnly, Category = "Sandevistan|VFX")
	UNiagaraSystem* SandevistanFX;

	/** Optional overlay PP-material (drag in the material instance) */
	UPROPERTY(EditDefaultsOnly, Category = "Sandevistan|VFX")
	UMaterialInterface* OverlayMaterial;

private:
	/** The spawned Niagara component we keep around for easy toggling */
	UPROPERTY()
	UNiagaraComponent* FXComp = nullptr;

	/** Handle so we can auto-deactivate */
	FTimerHandle TimerHandle_Deactivate;

	/** Helper that actually spawns / shows the effect */
	void SpawnOrEnableFX();
	void HideFX();
};
