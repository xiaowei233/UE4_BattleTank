// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "TankAimingComponent.generated.h"


UENUM()
enum class EAimingStatus: uint8
{
	Locked,
	Aiming,
	Reloading
};

class UTankBarrelComponent;
class UTankTurretComponent;
class AProjectile;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable)
		void SetBarrelTurret(UTankBarrelComponent* BarrelToSet, UTankTurretComponent* TurretToSet);

	UFUNCTION(BlueprintCallable)
		void SetProjectileBP(TSubclassOf<AProjectile> ProjectileBluePrint);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Fire();

	void AimAt(FVector, float = 10000.);

	void MoveBarrelTowards(FVector);

	EAimingStatus GetFireStatus();
protected:
	UPROPERTY(BlueprintReadOnly)
		EAimingStatus FireStatus = EAimingStatus::Reloading;

	UPROPERTY(EditAnywhere, Category = Firing)
		float FireSpeed = 10000.;
	UPROPERTY(EditAnywhere)
		float FireInterval = 1.0;

private:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving();
	UTankBarrelComponent* Barrel = nullptr;
	UTankTurretComponent* Turret = nullptr;

	float FireTime = 0.0;
	FVector AimingDirection;

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBP;
};
