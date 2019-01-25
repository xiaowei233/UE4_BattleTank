// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * This class defines how the tank will move, it communicates and assign force to the tracks of the tank
 */
class ATank;
class UTankTrackComponent;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	//Tell each track how fast to move forward
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveForward(float Throttle);
	//Tell each track how fast to move left/right
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveLeftRight(float Throttle);
	//Set the track
	UFUNCTION(BlueprintCallable, Category = SetUp)
		void SetTracks(UTankTrackComponent* LeftTrackToSet, UTankTrackComponent* RightTrackToSet);

protected:
	//For the AI to use so both player and AI use same moving system
	virtual void RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) override;

private:
	//Left track of the tank
	UTankTrackComponent* LeftTrack = nullptr;
	//Right track of the tank
	UTankTrackComponent* RightTrack = nullptr;
	//Check is the tank is moving forward or backward
	bool IsMovingForward = true;
};
