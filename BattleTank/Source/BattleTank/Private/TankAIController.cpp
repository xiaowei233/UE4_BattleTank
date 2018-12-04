// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"





ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController ControlledTank failed"));
	}

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController GetPlayerTank failed"));
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) {
		return nullptr;
	}
	return Cast<ATank>(PlayerTank);
}

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank() && GetControlledTank()) {
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}