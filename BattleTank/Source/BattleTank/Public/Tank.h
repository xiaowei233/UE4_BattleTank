// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Declare a delegate(the subject) event so the observers of this class can listen to it
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);
/**
* This class defines the behavior of the tank, which is the only battling vehicle that players & AIs
* can control.
*/
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//Declare the OnDeath event of this class Tank
	FTankDelegate OnDeath;

protected:
	//The current hit point of the tank
	UPROPERTY(EditAnywhere)
		float CurrentHitPoint = 3000.;
	//The maximum hit point of the tank
	UPROPERTY(EditAnywhere)
		float MaxHitPoint = 3000.;
	//Calculate the damage taken by this tank and all sorts of things
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;	

private:
	ATank();
};
