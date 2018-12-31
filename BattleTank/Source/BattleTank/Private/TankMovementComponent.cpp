// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"
#include "Tank.h"



void UTankMovementComponent::IntendMoveForward(float Throttle)
{
	if (!LeftTrack || !RightTrack || Throttle == 0) {
		IsMovingForward = true;
		return;
	}
	IsMovingForward = Throttle > 0;
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(Throttle);
}

void UTankMovementComponent::IntendMoveLeftRight(float Throttle)
{
	if (!LeftTrack || !RightTrack || Throttle == 0) {
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("%d"), IsMovingForward);
	if (IsMovingForward) {
		LeftTrack->SetThrottle(Throttle);
		RightTrack->SetThrottle(-Throttle);
	}
	else {
		LeftTrack->SetThrottle(-Throttle);	
		RightTrack->SetThrottle(Throttle);
	}

}

void UTankMovementComponent::SetTracks(UTankTrackComponent* LeftTrackToSet, UTankTrackComponent* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) {
		return;
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}