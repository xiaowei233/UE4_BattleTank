// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"



#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController ControlledTank failed"));
	}

	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController GetPlayerTank failed"));
	}
}

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	if (PlayerTank && ControlledTank) {
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at location %s"), *ControlledTank->GetName(), *PlayerTank->GetActorLocation().ToString())
	}
}