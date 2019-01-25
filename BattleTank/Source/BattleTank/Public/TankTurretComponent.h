// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurretComponent.generated.h"
/**
* This class is for defining the behavior of the turret part of the tank
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTurretComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankTurretComponent();

public:	
	//Rotate the turret	
	void RotateTurret(float);
	//the maximum rotating speed(degree) per second
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxRotateDPS = 20;
	//the maximum rotation the turret can do
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxRotateDegree = 75;
	//the mimum, the opposite of the maximum rotation
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinRotateDegree = -75;

};
