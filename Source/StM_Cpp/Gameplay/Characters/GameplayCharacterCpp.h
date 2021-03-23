// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StM_Cpp/StM_CppCharacter.h"

#include "GameplayCharacterCpp.generated.h"

class UHealthComponentCpp;
class UWeaponComponentCpp;
struct FWeaponStatsC;

/**
 * 
 */
UCLASS()
class STM_CPP_API AGameplayCharacterCpp : public AStM_CppCharacter
{
	GENERATED_BODY()
	


public:
	AGameplayCharacterCpp();

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UHealthComponentCpp* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UWeaponComponentCpp* WeaponComponent;

	UPROPERTY(BlueprintReadOnly, Replicated)
		bool bIsDead;

	UFUNCTION(BlueprintImplementableEvent)
		void OnHpChanges();




	/// Blueprint Event \\\


	UFUNCTION(Client, Unreliable)
		void NeedUpdateWidgetAmmo();

	UFUNCTION(Client, Unreliable)
		void NeedUpdateWidgetHealth();

	UFUNCTION(BlueprintImplementableEvent)
		void CharacterDead();

protected:
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateWidgetAmmo();

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateWidgetHealth();
};

