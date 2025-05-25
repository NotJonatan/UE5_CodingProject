// ZiplineActor.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZiplineActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class CODINGCPP_API AZiplineActor : public AActor
{
	GENERATED_BODY()

public:
	AZiplineActor();

	FVector GetStart() const { return LineStart; }
	FVector GetEnd()   const { return LineEnd; }
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Cable;
	UPROPERTY(VisibleAnywhere) UBoxComponent* Trigger;

	UPROPERTY(EditInstanceOnly) FVector LineStart;
	UPROPERTY(EditInstanceOnly) FVector LineEnd;


};
