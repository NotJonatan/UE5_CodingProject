#include "EnemySpawner.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"    // ← make sure this line is **exactly**:
//    #include "GameFramework/Pawn.h"

AEnemySpawner::AEnemySpawner()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AEnemySpawner::BeginPlay()
{
    Super::BeginPlay();
    SpawnedSoFar = 0;

    if (bUseInterval)
    {
        // start recurring timer
        GetWorld()->GetTimerManager().SetTimer(
            TimerHandle_Spawn,
            this, &AEnemySpawner::SpawnOne,
            SpawnInterval,
            true,    // looping
            0.f      // first fire immediately
        );
    }
    else
    {
        // just fire N times immediately
        for (int i = 0; i < SpawnCount; i++)
        {
            SpawnOne();
        }
    }
}

void AEnemySpawner::SpawnOne()
{
    if (SpawnedSoFar >= SpawnCount)
    {
        // stop the timer if we reached our quota
        if (bUseInterval)
        {
            GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Spawn);
        }
        return;
    }

    if (EnemyClasses.Num() == 0)
        return;

    // pick a random class from the array
    int32 Idx = FMath::RandRange(0, EnemyClasses.Num() - 1);
    TSubclassOf<APawn> PawnClass = EnemyClasses[Idx];
    if (!PawnClass)
        return;

    FActorSpawnParameters Params;
    Params.Owner = this;

    // spawn it as a Pawn*
    APawn* P = GetWorld()->SpawnActor<APawn>(
        PawnClass,
        GetActorLocation(),
        GetActorRotation(),
        Params
    );

    // if it actually spawned, give it its AI controller
    if (P)
    {
        P->SpawnDefaultController();
    }

    SpawnedSoFar++;
}
