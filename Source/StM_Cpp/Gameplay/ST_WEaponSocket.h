// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ST_WEaponSocket.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FWeaponSocketC
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
		FName ActiveSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
		FName HidenSocket;

	UPROPERTY()
		UObject* SafeObjectPointer;

};

