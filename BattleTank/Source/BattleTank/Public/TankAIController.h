// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Controller.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;
/**
* This class defines the behavior of the AIs in this game
*/
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;

	//Distance at which the AI will stop trying to move closer to the player
	UPROPERTY(EditAnywhere, Category = "Set Up")
	float AcceptanceRadius = 5000.;
	//Function for dealing with the TankDeath event of its possessed tank
	UFUNCTION()
		void OnTankDeath();
private:
	//AimingComponent for the AI controller
	UTankAimingComponent* AimingComponent = nullptr;
	//Possessed tank of the AI
	ATank* ControlledTank = nullptr;
	//Player tank that the AI will try to find and kill
	ATank* PlayerTank = nullptr;
	//Used only because didn't want to bind OnTankDeath at BeginPlay
	virtual void SetPawn(APawn* InPawn) override;
};
