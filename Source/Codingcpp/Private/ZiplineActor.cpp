// Fill out your copyright notice in the Description page of Project Settings.
#include "ZiplineActor.h"
#include "Engine/World.h"

// Sets default values
AZiplineActor::AZiplineActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZiplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Your zipline logic here…
}