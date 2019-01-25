// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelComponent.h"
#include "Engine/World.h"

void UTankBarrelComponent::Elevate(float Speed)
{

	Speed = FMath::Clamp<float>(Speed, -1, 1);
	auto ElevationChange = Speed * MaxElevateDPS * GetWorld()->DeltaTimeSeconds;
	auto NewElevation = RelativeRotation.Pitch + ElevationChange;

	auto AppliedElevation = FMath::Clamp<float>(NewElevation, MinElevationDegree, MaxElevationDegree);
	SetRelativeRotation(FRotator(AppliedElevation, 0, 0));
}