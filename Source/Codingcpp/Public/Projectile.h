// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class CODINGCPP_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector              NormalImpulse,
		const FHitResult& Hit);

	UPROPERTY(VisibleDefaultsOnly) UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly) class UProjectileMovementComponent* Move;
};