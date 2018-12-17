// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()



public:

	void Elevate(float);
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevateDPS = 2;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegree = 23;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegree = 0;



};
