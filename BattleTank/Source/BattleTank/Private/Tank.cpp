// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

//void ATank::MoveCamera(FVector ViewLocation)
//{
//	TankAimingComponent->MoveCamera(ViewLocation);
//}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, FiringVelocity);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	FireTime = GetWorld()->GetTimeSeconds();

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrelComponent *BarrelToSet)
{

	TankAimingComponent->SetBarrel(BarrelToSet);
	BarrelRef = BarrelToSet;

}

void ATank::Fire()
{
	if (!BarrelRef) { return; }
	float Now = GetWorld()->GetTimeSeconds();
	if (Now - FireTime <= FireInterval) {
		return;
	}
	FireTime = Now;

	AProjectile* FiredProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, BarrelRef->GetSocketLocation(FName("FiringLocation")), BarrelRef->GetSocketRotation(FName("FiringLocation")));
	FiredProjectile->LaunchProjectile(FiringVelocity);

}

void ATank::SetTurretReference(UTankTurretComponent* TurretToSet)
{
	TankAimingComponent->SetTurret(TurretToSet);
}
