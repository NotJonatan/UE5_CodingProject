// VaultComponent.h
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VaultComponent.generated.h"

UCLASS(ClassGroup = (Movement), meta = (BlueprintSpawnableComponent))
class CODINGCPP_API UVaultComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	bool TryVault(const FVector& ForwardCheckOrigin);

private:
	UPROPERTY(EditDefaultsOnly) float MaxVaultHeight = 120.f;
	UPROPERTY(EditDefaultsOnly) float VaultSpeed = 800.f;
};
