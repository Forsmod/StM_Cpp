// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ST_WeaponStats.generated.h"


/**
 * 
 */

USTRUCT(BlueprintType)
struct FWeaponStatsC
{
	GENERATED_BODY()	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
		int CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
		int MaxAmmoInClip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
		int AllAmmo;

	UPROPERTY()
		UObject* SafeObjectPointer;

};


