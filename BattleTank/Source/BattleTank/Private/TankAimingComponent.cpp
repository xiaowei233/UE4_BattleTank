// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankTurretComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"
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
		AimingDirection = TossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimingDirection);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Aiming Solution found"));
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimingDirection)
{
	auto CurrentAim = Barrel->GetForwardVector().Rotation();
	auto TargetAim = AimingDirection.Rotation();
	auto DeltaRotator = TargetAim - CurrentAim;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->RotateTurret(DeltaRotator.Yaw);
}

void UTankAimingComponent::SetBarrelTurret(UTankBarrelComponent * BarrelToSet, UTankTurretComponent * TurretToSet)
{
	if (!BarrelToSet || !BarrelToSet) {
		return;
	}
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}
void UTankAimingComponent::SetProjectileBP(TSubclassOf<AProjectile> ProjectileBluePrint)
{
	if (!ProjectileBluePrint) {
		return;
	}
	ProjectileBP = ProjectileBluePrint;
}
void UTankAimingComponent::BeginPlay()
{
	FireTime = GetWorld()->GetTimeSeconds();
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) {
		return false;
	}
	return !AimingDirection.Equals(Barrel->GetForwardVector(), 0.01);
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (GetWorld()->GetTimeSeconds() - FireTime < FireInterval) {
		FireStatus = EAimingStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FireStatus = EAimingStatus::Aiming;
	}
	else
	{
		FireStatus = EAimingStatus::Locked;
	}
	//UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAimingStatus"));
	//UE_LOG(LogTemp, Warning, TEXT("cuurent fire state: %s"), *(pEnum ? pEnum->GetNameStringByIndex(static_cast<uint8>(FireStatus)) : "null"));
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBP)) { return; }
	if (FireStatus != EAimingStatus::Reloading) {

		auto FiredProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Barrel->GetSocketLocation(FName("FiringLocation")), Barrel->GetSocketRotation(FName("FiringLocation")));
		FiredProjectile->LaunchProjectile(FireSpeed);
		FireTime = GetWorld()->GetTimeSeconds();
	}
}