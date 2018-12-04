// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankBarrelComponent.h"
#include "TankAimingComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
public:	

	void AimAt(FVector, float);
		
	void SetBarrel(UTankBarrelComponent*);

	void MoveBarrelTowards(FVector);

private:
	UTankBarrelComponent* Barrel = nullptr;
};
