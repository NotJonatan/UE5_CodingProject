//// ShooterComponent.cpp
//#include "ShooterComponent.h"
//#include "Projectile.h"
//#include "Camera/CameraComponent.h"
//#include "Kismet/GameplayStatics.h"
//#include "Engine/World.h"
//#include "GameFramework/Pawn.h"
//#include "TimerManager.h"
//
//UShooterComponent::UShooterComponent()
//{
//    PrimaryComponentTick.bCanEverTick = false;
//}
//
//void UShooterComponent::BeginPlay()
//{
//    Super::BeginPlay();
//}
//
//void UShooterComponent::StartFire()
//{
//    FireOnce();
//    if (FireInterval > 0.f)
//    {
//        GetWorld()->GetTimerManager()
//            .SetTimer(FireTimer, this, &UShooterComponent::FireOnce,
//                FireInterval, true, FireInterval);
//    }
//}
//
//void UShooterComponent::StopFire()
//{
//    GetWorld()->GetTimerManager().ClearTimer(FireTimer);
//}
//
//void UShooterComponent::FireOnce()
//{
//    if (!ProjectileClass) return;
//
//    ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
//    if (!OwnerChar) return;
//
//    // 1) Determine spawn transform — from camera or socket on mesh
//    FVector  MuzzleLocation;
//    FRotator MuzzleRotation;
//
//    if (UCameraComponent* Cam = OwnerChar->FindComponentByClass<UCameraComponent>())
//    {
//        MuzzleLocation = Cam->GetComponentLocation() + Cam->GetForwardVector() * 30.f;
//        MuzzleRotation = Cam->GetComponentRotation();
//    }
//    else
//    {
//        USceneComponent* MuzzleComp =
//            OwnerChar->GetMesh()->GetSocketByName(MuzzleSocket);
//        if (!MuzzleComp) return;
//
//        MuzzleLocation = MuzzleComp->GetComponentLocation();
//        MuzzleRotation = MuzzleComp->GetComponentRotation();
//    }
//
//    // 2) Spawn the projectile
//    FActorSpawnParameters Params;
//    Params.Owner = OwnerChar;
//    GetWorld()->SpawnActor<AActor>(ProjectileClass,
//        MuzzleLocation,
//        MuzzleRotation,
//        Params);
//}