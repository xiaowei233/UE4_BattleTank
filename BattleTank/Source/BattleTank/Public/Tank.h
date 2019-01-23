// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	FTankDelegate OnDeath;
protected:
	UPROPERTY(EditAnywhere)
		float CurrentHitPoint = 3000.;

	UPROPERTY(EditAnywhere)
		float MaxHitPoint = 3000.;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;	
private:
	ATank();

};
