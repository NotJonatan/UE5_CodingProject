//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
//#include "ShooterComponent.generated.h"
//
//
//class AProjectile;
//class ACharacter;
//
//UCLASS(ClassGroup = (Combat), meta = (BlueprintSpawnableComponent))
//class CODINGCPP_API UShooterComponent : public UActorComponent
//{
//    GENERATED_BODY()
//
//public:
//
//    UShooterComponent();
//
//    /** Press / release from input */
//    UFUNCTION(BlueprintCallable)          // optional but handy in BP
//        void StartFire();
//
//    UFUNCTION(BlueprintCallable)
//    void StopFire();
//
//    /** Gun muzzle socket or scene-component name on the character */
//    UPROPERTY(EditDefaultsOnly, Category = "Fire")
//    FName MuzzleSocket = "Muzzle";
//
//    /** Projectile to spawn (Blueprint subclass OK) */
//    UPROPERTY(EditDefaultsOnly, Category = "Fire")
//    TSubclassOf<AActor> ProjectileClass;
//
//    /** Seconds between shots (0 = single-shot) */
//    UPROPERTY(EditDefaultsOnly, Category = "Fire", meta = (ClampMin = "0.02"))
//    float FireInterval = 0.12f;
//
//protected:
//    virtual void BeginPlay() override;
//    void FireOnce();
//
//    FTimerHandle FireTimer;
//};