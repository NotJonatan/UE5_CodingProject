// Fill out your copyright notice in the Description page of Project Settings.


#include "RailSlideComponent.h"

// Sets default values for this component's properties
URailSlideComponent::URailSlideComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URailSlideComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URailSlideComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

