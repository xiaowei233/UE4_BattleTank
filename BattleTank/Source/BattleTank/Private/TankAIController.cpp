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
		else if (AimingComponent->GetFireStatus() == EAimingStatus::OutOfAmmo && !AimingComponent->IsReloading()) {
			AimingComponent->Reload();
		}
	}
}

void ATankAIController::OnTankDeath()
{
	if (!GetPawn()) {
		return;
	}
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) {
			return;
		}
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

