#include "EnemySpawner.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

AEnemySpawner::AEnemySpawner()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AEnemySpawner::BeginPlay()
{
    Super::BeginPlay();

    if (EnemyClasses.Num() == 0 || SpawnCount <= 0)
    {
        return;
    }

    SpawnedSoFar = 0;

    if (bUseSpawnInterval && SpawnInterval > 0.f)
    {
        // Start timer to call SpawnOne() every SpawnInterval seconds
        GetWorldTimerManager().SetTimer(
            TimerHandle_Spawn,
            this,
            &AEnemySpawner::SpawnOne,
            SpawnInterval,
            true);
    }
    else
    {
        // Fire them all off in one go
        for (int32 i = 0; i < SpawnCount; ++i)
        {
            SpawnOne();
        }
    }
}

void AEnemySpawner::SpawnOne()
{
    if (SpawnedSoFar >= SpawnCount)
    {
        // We're done—clear the timer if it’s running
        GetWorldTimerManager().ClearTimer(TimerHandle_Spawn);
        return;
    }

    // pick a random enemy class
    int32 Idx = FMath::RandRange(0, EnemyClasses.Num() - 1);
    if (TSubclassOf<AActor> ToSpawn = EnemyClasses[Idx])
    {
        FActorSpawnParameters Params;
        Params.Owner = this;
        GetWorld()->SpawnActor<AActor>(
            ToSpawn,
            GetActorLocation(),
            GetActorRotation(),
            Params);
    }

    ++SpawnedSoFar;
}
