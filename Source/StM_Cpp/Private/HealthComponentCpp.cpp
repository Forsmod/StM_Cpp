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

void UHealthComponentCpp::CurrentHP_Update_Implementation()
{
	OwnerRef->NeedUpdateWidgetHealth();
}

void UHealthComponentCpp::BeginPlay()
{
	UMainComponentCpp::BeginPlay();
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetMaxHP();
	}
	OwnerRef->OnTakeAnyDamage.AddDynamic(this, &UHealthComponentCpp::GetDamage);
}


void UHealthComponentCpp::GetDamage_Implementation(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	InstigatedByArray.AddUnique(InstigatedBy);
	LastDamageController = InstigatedBy;
	if (CurrentHP <= Damage)
	{
		CurrentHP = 0;
		Dead();
		return;
	}
	else
	{
		CurrentHP = CurrentHP - Damage;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Damage: x: %f"), Damage));
	CurrentHP_Update();
	
}

void UHealthComponentCpp::NewRound_Implementation()
{
	SetMaxHP();
	InstigatedByArray.Empty();
	LastDamageController = NULL;
}

void UHealthComponentCpp::Dead_Implementation()
{
	bIsDead = true;
	OwnerRef->bIsDead = true;
	OwnerRef->CharacterDead();

}



void UHealthComponentCpp::SetMaxHP_Implementation()
{
	CurrentHP = MaxHP;
}