// Source/Codingcpp/Public/UploadStationActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UploadStationActor.generated.h"

class UBoxComponent;

// Fired when the player with a drive overlaps the station
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUploadCompleted);

UCLASS()
class CODINGCPP_API AUploadStationActor : public AActor
{
    GENERATED_BODY()

public:
    AUploadStationActor();

protected:
    virtual void BeginPlay() override;

    /** Volume to detect player arrival */
    UPROPERTY(VisibleAnywhere, Category = "Upload")
    UBoxComponent* TriggerBox;

    /** Overlap callback */
    UFUNCTION()
    void OnBoxOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& Sweep
    );

    /** Blueprint hook for “upload succeeded” */
    UPROPERTY(BlueprintAssignable, Category = "Upload")
    FOnUploadCompleted OnUploadCompleted;
};
