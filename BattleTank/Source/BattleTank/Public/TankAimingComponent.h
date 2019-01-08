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
	Reloading,
	OutOfAmmo
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

	UFUNCTION(BlueprintCallable)
		void Reload();

	void AimAt(FVector, float = 10000.);

	void MoveBarrelTowards(FVector);

	bool IsReloading();
	EAimingStatus GetFireStatus();
	//int GetCurrentAmmo();
protected:
	UPROPERTY(BlueprintReadOnly)
		EAimingStatus FireStatus = EAimingStatus::Reloading;

	UPROPERTY(EditAnywhere, Category = Firing)
		float FireSpeed = 10000.;
	UPROPERTY(EditAnywhere)
		float FireInterval = 2.5;
	UPROPERTY(EditAnywhere)
		float ReloadInterval = 5.;
	UPROPERTY(EditAnywhere)
		int32 MaxAmmo = 7;
	UPROPERTY(BlueprintReadOnly)
		int32 CurrentAmmo = MaxAmmo;

private:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving();
	UTankBarrelComponent* Barrel = nullptr;
	UTankTurretComponent* Turret = nullptr;

	float FireTime = 0.0;
	float ReloadTime = 0.0;
	FVector AimingDirection;

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBP;
};
