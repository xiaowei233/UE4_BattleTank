// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include "Engine/World.h"

void UTankTrackComponent::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -2, 2);
}

void UTankTrackComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	ApplyDriveForce();
	//ApplySideForce();
	CurrentThrottle = 0;
}

void UTankTrackComponent::ApplySideForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto AccelerationCorrection = -SlippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * AccelerationCorrection / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrackComponent::ApplyDriveForce()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDriveForce;
	auto ForceLocation = GetComponentLocation();
	auto Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Tank->AddForceAtLocation(ForceApplied, ForceLocation);
}

UTankTrackComponent::UTankTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrackComponent::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrackComponent::OnHit);
}