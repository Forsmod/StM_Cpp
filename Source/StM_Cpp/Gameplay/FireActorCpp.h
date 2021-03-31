// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponActorCpp.h"
#include "StM_Cpp/Gameplay/Bullet/MainBulletCpp.h"
#include "FireActorCpp.generated.h"

/**
 * 
 */


UCLASS()
class STM_CPP_API AFireActorCpp : public AWeaponActorCpp
{
	GENERATED_BODY()

public:

	AFireActorCpp();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* BulletStart;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class AMainBulletCpp> BulletClass;
	
	UPROPERTY(BlueprintReadWrite)
		float AttackSpeed;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float ReloadTime;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		int AttackSpeedPerSec;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		bool AutomaticFire;

	UPROPERTY()
		FTimerHandle LoopFireHandle;

	UPROPERTY()
		FTimerHandle SecondFire;

	UPROPERTY()
		FTimerHandle ReloadHandle;

	UPROPERTY()
		bool SetFire;
	
	UPROPERTY()
		bool IsReload;

	virtual void StartFire() override;

	virtual void EndFire() override;

	virtual void BeginPlay() override;

	UFUNCTION()
		void Loop();

	UFUNCTION()
		void TryShoot();

	
	UFUNCTION(BlueprintCallable, Server, Unreliable)
		void StartReload();

	UFUNCTION()
		void EndReload();

	UFUNCTION()
		void EndTimeSecondFire();

	UFUNCTION()
		FTransform FindBulletTransform(FVector Target);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		void SpawnBulletMulticast(FTransform Transform);

	





	//////Blueprint event

	
	
	
};
