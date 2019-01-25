// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

/**
* Define the different states a tank's firing system can be in
*/
UENUM()
enum class EAimingStatus: uint8
{
	Locked,
	Aiming,
	Reloading,
	OutOfAmmo
};

class UTankBarrelComponent;
class UTankTurretComponent;
class AProjectile;
/**
* This class defines how the tank can aim and how the tank will fire 
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//Set the barrel of the tank to this aiming component
	UFUNCTION(BlueprintCallable)
		void SetBarrelTurret(UTankBarrelComponent* BarrelToSet, UTankTurretComponent* TurretToSet);
	//set the projectile blueprint for the aiming component
	UFUNCTION(BlueprintCallable)
		void SetProjectileBP(TSubclassOf<AProjectile> ProjectileBluePrint);
	//Tell the tank to fire through this aiming component
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Fire();
	//tell the tank to relod its ammo
	UFUNCTION(BlueprintCallable)
		void Reload();
	//Aim the tank toward the aiming solution the controllers find
	void AimAt(FVector, float = 10000.);
	//Move the tank's barrel and turret towards where it's aiming at
	void MoveBarrelTowards(FVector);
	//Return true if the tank is reloading its ammo
	bool IsReloading();
	//Return the current firing state of the tank
	EAimingStatus GetFireStatus();

protected:
	//Set the default firing state of the tank to be Reloading
	UPROPERTY(BlueprintReadOnly)
		EAimingStatus FireStatus = EAimingStatus::Reloading;
	//The speed of the projectile
	UPROPERTY(EditAnywhere, Category = Firing)
		float FireSpeed = 10000.;
	//The interval at which the tank can fire its projectiles
	UPROPERTY(EditAnywhere)
		float FireInterval = 2.5;
	//The reloading time of the tank to fully relaod its ammo
	UPROPERTY(EditAnywhere)
		float ReloadInterval = 5.;
	//The maximum ammo of the tank
	UPROPERTY(EditAnywhere)
		int32 MaxAmmo = 7;
	//The current ammo of the tank, initialize to be maxammo at BeginPlay
	UPROPERTY(BlueprintReadOnly)
		int32 CurrentAmmo;

private:
	UTankAimingComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	//Check if the barrel is still moving(e.g. barrel not aiming at the aiming solution of the tank)
	bool IsBarrelMoving();
	//The barrel for aiming component
	UTankBarrelComponent* Barrel = nullptr;
	//the turret for aiming component
	UTankTurretComponent* Turret = nullptr;
	//The firing timer of the tank
	float FireTime = 0.0;
	//the reload timer of the tank
	float ReloadTime = 0.0;
	//The aiming direction of which the projectile will be launched
	FVector AimingDirection;
	//The projectile to be launch at Fire()
	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBP;
};
