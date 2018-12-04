// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float FiringVelocity)
{
	if (!Barrel) {
		return;
	}
	FVector TossVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("FiringLocation"));
	auto TankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation();
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		TossVelocity,
		StartLocation,
		HitLocation,
		FiringVelocity,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*, FDefaultAllocator>(),
		false
	)) {
		auto AimingDirection = TossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimingDirection);

		UE_LOG(LogTemp, Warning, TEXT("Tank %s is aiming at %s"), *TankName, *AimingDirection.ToString());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Aiming Solution found"));
	}
}

void UTankAimingComponent::SetBarrel(UTankBarrelComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimingDirection)
{
	auto CurrentAim = Barrel->GetForwardVector().Rotation();
	auto TargetAim = AimingDirection.Rotation();
	Barrel->Elevate(0.3);
}

