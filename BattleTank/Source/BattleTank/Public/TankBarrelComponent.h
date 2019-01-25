// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

/**
 * This class defines the bahavior of the barrel of the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//Elevate the barrel
	void Elevate(float);
	//the maximum degree per second that the barrel can elevate
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevateDPS = 10;
	//the maximum elevation
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegree = 36;
	//the minimum elevation
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegree = 0;



};
