// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"


float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	CurrentHitPoint = CurrentHitPoint - FMath::Clamp<float>(DamageAmount, 0, CurrentHitPoint);
	if (CurrentHitPoint <= 0) {
		//Broadcast the TankDeath event to the possessing observers(controllers)
		OnDeath.Broadcast();
	}
	return 0.0f;
}

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}
