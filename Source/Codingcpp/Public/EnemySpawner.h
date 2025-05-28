#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

// forward-declare APawn so we don’t need the full header here
class APawn;

UCLASS()
class CODINGCPP_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;

	// this actually does the spawn
	void SpawnOne();

	// keep track of how many we’ve made
	int32 SpawnedSoFar = 0;

	// timer handle if you do interval spawns
	FTimerHandle TimerHandle_Spawn;

public:
	// **Which Pawn Blueprints to pick from**  
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<TSubclassOf<APawn>> EnemyClasses;

	// **Total to spawn** (if not using interval, we’ll spawn them all at BeginPlay)
	UPROPERTY(EditAnywhere, Category = "Spawning")
	int32 SpawnCount = 5;

	// **Turn on/off interval spawning**  
	UPROPERTY(EditAnywhere, Category = "Spawning")
	bool bUseInterval = true;

	// **If interval is on, how many seconds between each spawn**  
	UPROPERTY(EditAnywhere, Category = "Spawning", meta = (EditCondition = "bUseInterval"))
	float SpawnInterval = 2.f;
};
