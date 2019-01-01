// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
class ATank;
class UTankTrackComponent;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveForward(float Throttle);
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveLeftRight(float Throttle);

	UFUNCTION(BlueprintCallable, Category = SetUp)
		void SetTracks(UTankTrackComponent* LeftTrackToSet, UTankTrackComponent* RightTrackToSet);

protected:
	virtual void RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) override;


private:

	UTankTrackComponent* LeftTrack = nullptr;
	UTankTrackComponent* RightTrack = nullptr;

	bool IsMovingForward = true;
};
