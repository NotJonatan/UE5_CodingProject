#include "RailSlideComponent.h"
#include "RailSplineActor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

URailSlideComponent::URailSlideComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // manual tick
}

void URailSlideComponent::BeginPlay()
{
	Super::BeginPlay();
	if (ACharacter* C = Cast<ACharacter>(GetOwner()))
	{
		MoveComp = C->GetCharacterMovement();
	}
}

bool URailSlideComponent::TryStartSlide(ARailSplineActor* Rail, float StartAlpha)
{
	if (!Rail || bSliding || !MoveComp) return false;

	bSliding = true;
	CurrentRail = Rail;
	SlideAlpha = FMath::Clamp(StartAlpha, 0.f, 1.f);

	MoveComp->SetMovementMode(MOVE_Flying);         // simple: disable gravity
	return true;
}

void URailSlideComponent::TickSlide(float DeltaTime)
{
	if (!bSliding || !CurrentRail) return;

	SlideAlpha += (SlideSpeed / CurrentRail->GetSpline()->GetSplineLength()) * DeltaTime;

	FVector Loc, Tan;
	CurrentRail->GetPoint(SlideAlpha, Loc, Tan);

	GetOwner()->SetActorLocation(Loc);
	GetOwner()->SetActorRotation(Tan.Rotation());

	if (SlideAlpha >= 1.f) EndSlide();
}

void URailSlideComponent::EndSlide()
{
	if (!bSliding) return;
	bSliding = false;
	CurrentRail = nullptr;

	if (MoveComp) MoveComp->SetMovementMode(MOVE_Walking);
}
