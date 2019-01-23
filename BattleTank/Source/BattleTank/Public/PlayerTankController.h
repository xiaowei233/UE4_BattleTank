// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Controller.h"

#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "PlayerTankController.generated.h"

/**
 * 
 */
class ATank;
class UTankAimingComponent;
UCLASS(Blueprintable)
class BATTLETANK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
	

public:
	UFUNCTION()
		void OnTankDeath();

protected:
	UFUNCTION(BlueprintCallable, Category = "SetUp")
		ATank* GetControlledTank() const;
	UFUNCTION(BlueprintImplementableEvent, Category = "SetUp")
		void FindAimingComponent(UTankAimingComponent* AimingComponent);

private:
	UTankAimingComponent* AimingComponent = nullptr;
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

	virtual void SetPawn(APawn* InPawn) override;

};
