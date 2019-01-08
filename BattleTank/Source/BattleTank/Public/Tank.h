// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
		float CurrentHitPoint = 3000.;

	UPROPERTY(BlueprintReadOnly)
		float MaxHitPoint = 3000.;
private:
	ATank();
};
