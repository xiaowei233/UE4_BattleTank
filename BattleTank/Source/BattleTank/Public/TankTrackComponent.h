// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"
/**
* This class is defining how the track of the tank will work, how the track will
* apply independent driving force onto itself and make the tank move
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//Set the force to be applied onto the track
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

private:
	UTankTrackComponent();
	virtual void BeginPlay() override;

	//Check if the track is on ground
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	//Eliminate the damping residual
	void ApplySideForce();
	//Apply the forward/backward throttle onto the track
	void ApplyDriveForce();
	//The maximum speed one track can achieve
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDriveForce = 73000000.0;
	//the current throttle/speed of the track
	float CurrentThrottle = 0;
};
