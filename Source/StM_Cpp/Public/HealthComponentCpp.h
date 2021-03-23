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

	UFUNCTION(Client, Unreliable)
		void CurrentHP_Update();

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateWidgetServer();

	UPROPERTY(BlueprintReadOnly)
		bool bIsDead;

	UPROPERTY(BlueprintReadOnly)
		TArray<AController*> InstigatedByArray;

	UPROPERTY(BlueprintReadOnly)
		AController* LastDamageController;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* EmitterTamplate;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void SetMaxHP();

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void GetDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void Dead();

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void NewRound();


};
