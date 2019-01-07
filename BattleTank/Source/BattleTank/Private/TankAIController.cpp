// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController ControlledTank failed"));
	}
	else {
		AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	}

	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//UE_LOG(LogTemp,Warning, TEXT("Player Tank Name: %s"), *PlayerTank->GetName());
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController GetPlayerTank failed"));
	}
}

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	if (ensure(PlayerTank && ControlledTank && AimingComponent)) {
		MoveToActor(PlayerTank, AcceptanceRadius);
		AimingComponent->AimAt(PlayerTank->GetActorLocation()+FVector(0, 0, 100));	
		if (AimingComponent->GetFireStatus() == EAimingStatus::Locked) {
			AimingComponent->Fire();

		}
	}
}

