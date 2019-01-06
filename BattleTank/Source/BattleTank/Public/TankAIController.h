// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Controller.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


class ATank;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float) override;

private:
	UTankAimingComponent* AimingComponent = nullptr;
	ATank* ControlledTank = nullptr;
	ATank* PlayerTank = nullptr;

	float MinRange = 1600.;
	float MaxRange = 5200.;
	float AcceptanceRadius = FMath::RandRange(MinRange, MaxRange);
};
