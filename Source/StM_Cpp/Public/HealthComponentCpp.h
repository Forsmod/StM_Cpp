// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainComponentCpp.h"
#include "HealthComponentCpp.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class STM_CPP_API UHealthComponentCpp : public UMainComponentCpp
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, ReplicatedUsing = OnRep_CurrentHP)
		float CurrentHP;

	UFUNCTION()
		void OnRep_CurrentHP();

	UFUNCTION(BlueprintImplementableEvent)
		void CurrentHP_Update();

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateWidgetServer();

	UPROPERTY(BlueprintReadOnly)
		bool bIsDead;

	UPROPERTY(BlueprintReadOnly)
		TArray<AController*> DamageCausers;

	UPROPERTY(BlueprintReadOnly)
		AController* LastDamageController;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void SetMaxHP();

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void GetDamage(float Damage, AController* Causer);

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void Dead();

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void NewRound();

	UFUNCTION(BlueprintImplementableEvent)
		void DeadBP();
};
