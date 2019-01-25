// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"
#include "Engine/World.h"

UTankTurretComponent::UTankTurretComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTurretComponent::RotateTurret(float Speed)
{
	Speed = FMath::Clamp<float>(Speed, -1, 1);
	auto RotationChange = Speed * MaxRotateDPS * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}

