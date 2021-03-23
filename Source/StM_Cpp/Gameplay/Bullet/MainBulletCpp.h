// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


#include "MainBulletCpp.generated.h"

UCLASS()
class STM_CPP_API AMainBulletCpp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainBulletCpp();

	UPROPERTY()
		float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY()
		FTimerHandle DestroyTimer;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* EmitterBlood;
	
	UFUNCTION()
		void DestroyBullet();

	UFUNCTION()
		void OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnBoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* BulletMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};


