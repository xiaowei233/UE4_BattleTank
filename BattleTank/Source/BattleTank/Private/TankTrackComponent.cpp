// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"

void UTankTrackComponent::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDriveForce;
	auto ForceLocation = GetComponentLocation();
	auto Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Tank->AddForceAtLocation(ForceApplied, ForceLocation);
}