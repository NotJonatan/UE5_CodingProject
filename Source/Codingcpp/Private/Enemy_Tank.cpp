// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Tank.h"

// Sets default values
AEnemy_Tank::AEnemy_Tank()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy_Tank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy_Tank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy_Tank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

