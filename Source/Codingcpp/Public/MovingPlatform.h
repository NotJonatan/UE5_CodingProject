#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

class UStaticMeshComponent;
class UDamageType;

UCLASS()
class CODINGCPP_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	// -- visuals & collision --
	UPROPERTY(VisibleAnywhere, Category = "Platform")
	UStaticMeshComponent* PlatformMesh;

	// -- back-&-forth movement points --
	UPROPERTY(EditInstanceOnly, Category = "Movement")
	FVector PointA;

	UPROPERTY(EditInstanceOnly, Category = "Movement")
	FVector PointB;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "1"))
	float MoveSpeed = 200.f;

	// -- damage settings --
	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageAmount = 20.f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;

private:
	FVector CurrentTarget;

	// swap end-points when we arrive
	void SwapTargetIfNeeded();

	// called when something overlaps the mesh
	UFUNCTION()
	void OnPlatformOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
