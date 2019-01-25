// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "PlayerTankController.generated.h"

class ATank;
class UTankAimingComponent;
/**
* This class is responsible for constructing a player controller to control the tank.
* It provides methods to define player behavior such as Spawn/Destroy and Aim/Fire
* It is an observer to the actual tank that this class will control.
*/
UCLASS(Blueprintable)
class BATTLETANK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
	

public:
	//The callback function for the observer pattern on event TankDeath
	UFUNCTION()
		void OnTankDeath();

protected:
	//Get currently controlled tank
	UFUNCTION(BlueprintCallable, Category = "SetUp")
		ATank* GetControlledTank() const;
	//Return the aiming component to the blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "SetUp")
		void FindAimingComponent(UTankAimingComponent* AimingComponent);

private:
	UTankAimingComponent* AimingComponent = nullptr;
	virtual void BeginPlay() override;
	virtual void Tick(float) override;

	//Provide the aim solution of where the player is aiming in the world
	void AimTowardCrosshair();
	//Helper method for the AimTowardCrosshair, served as a straight ray tracer
	bool GetSightRayHitLocation(FVector&) const;
	//The distance for the ray tracer
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.;

	//Horizontal location of where the crosshair is at in the player UI
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;
	//Vertical location of where the crosshair is at in the player UI
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.333333;

	//Used only because don't want to bind OnTankDeath callback at BeginPlay;
	virtual void SetPawn(APawn* InPawn) override;
};
