// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankTurretComponent::UTankTurretComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankTurretComponent::RotateTurret(float Speed)
{
	//UE_LOG(LogTemp, Warning, TEXT("%f"), speed);

	auto RotationChange = Speed * MaxRotateDPS * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;

	auto AppliedRotation = FMath::Clamp<float>(NewRotation, MinRotateDegree, MaxRotateDegree);
	SetRelativeRotation(FRotator(0, AppliedRotation, 0));
}

