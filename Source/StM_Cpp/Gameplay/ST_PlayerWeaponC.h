// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponActorCpp.h"
#include "ST_WeaponStats.h"
#include "CoreMinimal.h"
#include "ST_PlayerWeaponC.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerWeaponC
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
		TSubclassOf<class AWeaponActorCpp> Weapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
		FWeaponStatsC WeaponInfo;

	UPROPERTY()
		UObject* SafeObjectPointer;

};
