// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;
class URadialForceComponent;
/*
* This is the class defining the properties of the only projectile in this game, the explosive projectile that
* every tank is able to shoot.
*/
UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	//Launch the spawned projectile at a desirable speed
	void LaunchProjectile(float);
protected:
	//The collision mesh for the projectile
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* CollisionMesh = nullptr;
	//The at launch blast VFX/particle system for the projectile
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* LaunchBlast = nullptr;
	//The at impact blast VFX/particle system for the projectile
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* ImpactBlast = nullptr;
	//The impact radius of the projectile
	UPROPERTY(VisibleAnywhere, Category = "Components")
		URadialForceComponent* RadiusForce = nullptr;
	//How long the projectile will stay in the world after making an impact
	UPROPERTY(EditDefaultsOnly)
		float DestroyDelay = 2.5;
	//The base damage of the projectile
	UPROPERTY(EditDefaultsOnly)
		float BaseDamage = 700.;
	//Deal with the effects to trigger and damages to calculate
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	AProjectile();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	//Destroy the actor
	void DestroyActor();
	//The component for making the projectile move
	UProjectileMovementComponent* ProjectileMovementComponent;
};
