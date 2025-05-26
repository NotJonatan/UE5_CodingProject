// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

//Niagara
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "SandevistanComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODINGCPP_API USandevistanComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USandevistanComponent();

	/** Call from input, ability, etc. */
	UFUNCTION(BlueprintCallable, Category = "Sandevistan")
	void ActivateSandevistan(float Duration = 5.f);

	/** Asset you pick in the Details panel (a Niagara System) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX")
	UNiagaraSystem* VFXSystem = nullptr;

	/** Optional overlay PP-material (drag in the material instance) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VFX")
	UNiagaraComponent* VFXComponent = nullptr;


protected:
	virtual void BeginPlay() override;

};