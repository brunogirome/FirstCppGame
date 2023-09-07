// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMoveComponent::EnableMovement(bool ShouldMove)
{
	canItMove = ShouldMove;
	SetComponentTickEnabled(canItMove);
}

void UMoveComponent::SwitchMovement()
{
	canItMove = !canItMove;

	SetComponentTickEnabled(canItMove);
}

void UMoveComponent::BackToOriginalPosition()
{
	currentDistance = 0.f;

	SetRelativeLocation(StartRelativeLocation);
}

void UMoveComponent::SetMoveDirection(int direction)
{
	movementDirection = direction >= 1 ? 1 : -1;
}

// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	StartRelativeLocation = GetRelativeLocation();

	MoveOffsetNormalize = MoveOffset;
	MoveOffsetNormalize.Normalize();

	maxDistance = MoveOffset.Length();

	SetComponentTickEnabled(canItMove);

}

// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	currentDistance += DeltaTime * speed * movementDirection;

	if (currentDistance >= maxDistance || currentDistance <= 0.f) {
		movementDirection *= -1;
		
		OnEndpointReached.Broadcast(currentDistance >= maxDistance);

		currentDistance = FMath::Clamp(currentDistance, 0.f, maxDistance);
	}

	SetRelativeLocation(StartRelativeLocation + MoveOffsetNormalize * currentDistance);
}
