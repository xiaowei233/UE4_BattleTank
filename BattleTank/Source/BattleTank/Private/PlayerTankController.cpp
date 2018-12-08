// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTankController.h"



ATank* APlayerTankController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void APlayerTankController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController %s"), *(ControlledTank->GetName()));
	}

}

void APlayerTankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();

}

void APlayerTankController::AimTowardCrosshair()
{
	if (!GetControlledTank()) {
		return;
	}
	//FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
	//FVector MyLocation = GetOwner()->GetActorLocation();
	//FVector Direction = MyLocation - CameraLocation;

	//GetControlledTank()->MoveCamera(Direction);
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
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
