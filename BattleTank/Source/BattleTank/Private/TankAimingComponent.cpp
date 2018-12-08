// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankTurretComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "TankBarrelComponent.h"

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
	if (!Barrel || !Turret) {
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
		//UE_LOG(LogTemp, Warning, TEXT("Tank %s is aiming at %s"), *TankName, *AimingDirection.ToString());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Aiming Solution found"));
	}
}

void UTankAimingComponent::SetBarrel(UTankBarrelComponent * BarrelToSet)
{
	if (BarrelToSet) {
		Barrel = BarrelToSet;
	}
}

void UTankAimingComponent::SetTurret(UTankTurretComponent* TurretToSet)
{
	if (TurretToSet) {
		Turret = TurretToSet;
	}
}
//
//void UTankAimingComponent::MoveCamera(FVector ViewLocation)
//{
//	auto CurrentAim = Barrel->GetForwardVector().Rotation();
//	auto TargetAim = ViewLocation.Rotation();
//	auto DeltaRotator = TargetAim - CurrentAim;
//	Barrel->Elevate(DeltaRotator.Pitch);
//	Turret->RotateTurret(DeltaRotator.Yaw);
//}
void UTankAimingComponent::MoveBarrelTowards(FVector AimingDirection)
{
	auto CurrentAim = Barrel->GetForwardVector().Rotation();
	auto TargetAim = AimingDirection.Rotation();
	auto DeltaRotator = TargetAim - CurrentAim;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->RotateTurret(DeltaRotator.Yaw);
}

