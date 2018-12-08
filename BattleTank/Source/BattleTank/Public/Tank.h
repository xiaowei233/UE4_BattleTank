// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "Tank.generated.h"


class UTankTurretComponent;
class UTankBarrelComponent;
class UTankAimingComponent;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	//void MoveCamera(FVector);
	void AimAt(FVector);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:	
	UTankAimingComponent* TankAimingComponent = nullptr;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrelComponent* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Fire();

	float FireTime = 0.0;
	UPROPERTY(EditAnywhere)
	float FireInterval = 3.0;
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurretComponent* TurretToSet);
	UPROPERTY(EditAnywhere, Category = Firing)
		float FiringVelocity = 100000.;
};
