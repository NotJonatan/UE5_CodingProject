#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class CODINGCPP_API AEnemySpawner : public AActor
{
    GENERATED_BODY()

public:
    AEnemySpawner();

protected:
    virtual void BeginPlay() override;

    /** Which enemy Blueprints to pick from */
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TArray<TSubclassOf<AActor>> EnemyClasses;

    /** Total number of enemies to spawn */
    UPROPERTY(EditAnywhere, Category = "Spawning", meta = (ClampMin = "1"))
    int32 SpawnCount = 1;

    /** Seconds between each spawn when using interval */
    UPROPERTY(EditAnywhere, Category = "Spawning", meta = (ClampMin = "0.0"))
    float SpawnInterval = 0.5f;

    /** If true, will space them out by SpawnInterval; if false, spawns all at once */
    UPROPERTY(EditAnywhere, Category = "Spawning")
    bool bUseSpawnInterval = true;

private:
    int32 SpawnedSoFar = 0;
    FTimerHandle TimerHandle_Spawn;

    /** Called by timer to actually do one spawn */
    void SpawnOne();
};
