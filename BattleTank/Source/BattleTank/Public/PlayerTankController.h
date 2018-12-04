// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Controller.h"
#include "Engine/world.h"
#include "Tank.h"

#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "PlayerTankController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override;

	virtual void Tick(float) override;

	void AimTowardCrosshair();

	bool GetSightRayHitLocation(FVector&) const;

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.333333;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.;
};
