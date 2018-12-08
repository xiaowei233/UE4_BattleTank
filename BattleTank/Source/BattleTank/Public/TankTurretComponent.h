// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurretComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTurretComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankTurretComponent();

protected:

public:	
		
	void RotateTurret(float);
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxRotateDPS = 5;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxRotateDegree = 70;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinRotateDegree = -70;

};
