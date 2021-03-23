// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainComponentCpp.h"
#include "StM_Cpp/Gameplay/ST_PlayerWeaponC.h"



#include "WeaponComponentCpp.generated.h"

class AWeaponActorCpp;

struct FPlayerWeaponC;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class STM_CPP_API UWeaponComponentCpp : public UMainComponentCpp
{
	GENERATED_BODY()

public:

	UWeaponComponentCpp();

	UPROPERTY(BlueprintReadWrite, Replicated, ReplicatedUsing = OnCurrentWeaponChanges)
		AWeaponActorCpp* CurrentWeapon;
	
	UPROPERTY(BlueprintReadWrite)
		TArray<FPlayerWeaponC> PlayerWeaponsArray;

	UPROPERTY(BlueprintReadWrite)
		bool CanFire = true;


	UFUNCTION(BlueprintCallable)
		void OnCurrentWeaponChanges();
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
		void AddWeaponAuto(AWeaponActorCpp* Weapon);

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void AddWeaponManual(AWeaponActorCpp* Weapon);

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void PreAttachWeapon(int WeaponSlot);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
		void AttachWeaponMulticast(AWeaponActorCpp* Weapon);

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void DropWeapon(EWeaponTypeC WeaponType);

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void RemoveWeaponFromSlot(int WeaponSlot);

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void SelectValidSlot();

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void TryToSelectWeapon(EWeaponTypeC WeaponType);

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void SwapWeapon(EWeaponTypeC WeaponType);	

	UFUNCTION(BlueprintCallable)
		bool SlotValid(EWeaponTypeC WeaponType);

	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable)
		void DisableCollision(AWeaponActorCpp* Weapon);

	UFUNCTION(BlueprintCallable, NetMulticast, Unreliable)
		void EnableCollision(AWeaponActorCpp* Weapon);

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateWidgetAmmoClient();

	UFUNCTION()
		void SaveWeaponToSlot(AWeaponActorCpp* Weapon);

	UFUNCTION()
		void SaveStatsInWeapon(AWeaponActorCpp* DroppedWeapon);

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void StartFireServer();

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void EndFireServer();

	UFUNCTION(BlueprintCallable, Client, Unreliable)
		void NeedUpdateWidget();


	
};
