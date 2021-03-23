// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayCharacterCpp.h"
#include "StM_Cpp/Public/HealthComponentCpp.h"
#include "StM_Cpp/Public/WeaponComponentCpp.h"
#include "GameFramework/Actor.h"

#include "Components/CapsuleComponent.h"


void AGameplayCharacterCpp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGameplayCharacterCpp, bIsDead);
}

AGameplayCharacterCpp::AGameplayCharacterCpp()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponentCpp>(TEXT("HealthComponent"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponentCpp>(TEXT("WeaponComponent"));
}


void AGameplayCharacterCpp::NeedUpdateWidgetHealth_Implementation()
{
	UpdateWidgetHealth();
}

void AGameplayCharacterCpp::NeedUpdateWidgetAmmo_Implementation()
{
	UpdateWidgetAmmo();
}

