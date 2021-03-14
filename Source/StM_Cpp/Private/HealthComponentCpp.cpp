// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponentCpp.h"

void UHealthComponentCpp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UHealthComponentCpp, CurrentHP, COND_OwnerOnly);

}




void UHealthComponentCpp::OnRep_CurrentHP()
{
	CurrentHP_Update();

}

void UHealthComponentCpp::BeginPlay()
{
	UMainComponentCpp::BeginPlay();
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetMaxHP();
	}
}

void UHealthComponentCpp::NewRound_Implementation()
{
	SetMaxHP();
	DamageCausers.Empty();
	LastDamageController = NULL;
}

void UHealthComponentCpp::Dead_Implementation()
{
	bIsDead = true;
	DeadBP();

}

void UHealthComponentCpp::GetDamage_Implementation(float Damage, AController* Causer)
{
	DamageCausers.AddUnique(Causer);
	LastDamageController = Causer;
	if (CurrentHP < Damage)
	{
		CurrentHP = 0;
		Dead();
	}
	else
	{
		CurrentHP = CurrentHP - Damage;
	}
	UpdateWidgetServer();
}


void UHealthComponentCpp::SetMaxHP_Implementation()
{
	CurrentHP = MaxHP;
}