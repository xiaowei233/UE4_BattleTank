// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "Tank.generated.h"


class UTankTurretComponent;
class UTankBarrelComponent;
class AProjectile;
class UTankAimingComponent;
class UTankMovementComponent;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	//void MoveCamera(FVector);
	void AimAt(FVector);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent* TankMovementComponent = nullptr;

private:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrelComponent* BarrelToSet);


	UTankBarrelComponent* BarrelRef;

	float FireTime = 0.0;
	UPROPERTY(EditAnywhere)
	float FireInterval = 1.0;
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurretComponent* TurretToSet);
	UPROPERTY(EditAnywhere, Category = Firing)
		float FiringVelocity = 10000.;

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBP;
};
