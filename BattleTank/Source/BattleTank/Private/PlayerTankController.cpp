// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTankController.h"
#include "TankAimingComponent.h"
#include "Engine/world.h"
#include "Tank.h"

ATank* APlayerTankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void APlayerTankController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	bool IsMainMenu = GetWorld()->GetMapName() == "UEDPIE_0_StartMap";
	if (ensure(AimingComponent) && !IsMainMenu) {
		FindAimingComponent(AimingComponent);
		UE_LOG(LogTemp, Warning, TEXT("The Aiming Component is found %s."), *GetWorld()->GetMapName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("The Aiming Component is not found."));
	}
}

void APlayerTankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}

void APlayerTankController::AimTowardCrosshair()
{
	if (!GetControlledTank() || !AimingComponent) {
		return;
	}
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		AimingComponent->AimAt(HitLocation);
	}
}

bool APlayerTankController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportX, ViewportY;
	GetViewportSize(ViewportX, ViewportY);
	auto ScreenLocation = FVector2D(ViewportX * CrosshairXLocation, ViewportY * CrosshairYLocation);

	FVector WorldLocation, WorldDirection;
	FHitResult HitResult;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection)) {

		if (GetWorld()->LineTraceSingleByChannel(
				HitResult,
				PlayerCameraManager->GetCameraLocation(),
				PlayerCameraManager->GetCameraLocation() + WorldDirection * LineTraceRange,
				ECollisionChannel::ECC_Visibility)
			) 
		{
			OutHitLocation = HitResult.Location;
			return true;
		}
	}
	OutHitLocation = FVector(0);
	return false;
}

void APlayerTankController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) {
			return;
		}
		PossessedTank->OnDeath.AddUniqueDynamic(this, &APlayerTankController::OnTankDeath);
	}
}


void APlayerTankController::OnTankDeath()
{
	StartSpectatingOnly();
}