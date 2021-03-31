// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponentCpp.h"

#include "StM_Cpp/Gameplay/WeaponActorCpp.h"
#include "StM_Cpp/Gameplay/ST_WEaponSocket.h"
#include "StM_Cpp/Gameplay/ST_WeaponStats.h"
#include "StM_Cpp/Gameplay/EWeaponTypeCpp.h"


void UWeaponComponentCpp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponComponentCpp, CurrentWeapon);

}


UWeaponComponentCpp::UWeaponComponentCpp()
{
	PlayerWeaponsArray.Init(FPlayerWeaponC(), 6);
}

void UWeaponComponentCpp::OnCurrentWeaponChanges()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Changes"));

	if (IsValid(CurrentWeapon))
	{
		UMeshComponent* Mesh = CurrentWeapon->WeaponMesh;

		DisableCollision(CurrentWeapon);
		Mesh->AttachToComponent(OwnerRef->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, CurrentWeapon->WeaponSocket.ActiveSocket);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attach"));
		
	}
	NeedUpdateWidget();
}


bool UWeaponComponentCpp::SlotValid(EWeaponTypeC WeaponType)
{
	if (IsValid(PlayerWeaponsArray[WeaponType].Weapon))
		return true;
	else
		return false;
}

void UWeaponComponentCpp::EnableCollision_Implementation(AWeaponActorCpp* Weapon)
{
	if (IsValid(Weapon))
	{
		Weapon->CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Weapon->CapsuleCollision->SetSimulatePhysics(true);
	}
	
}

void UWeaponComponentCpp::DisableCollision_Implementation(AWeaponActorCpp* Weapon)
{
	if (IsValid(Weapon))
	{
		Weapon->CapsuleCollision->SetSimulatePhysics(false);
		Weapon->CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}


void UWeaponComponentCpp::SaveWeaponToSlot(AWeaponActorCpp* Weapon)
{
	EWeaponTypeC WeaponType = Weapon->WeaponType;
	PlayerWeaponsArray[WeaponType].Weapon = Weapon->GetClass();
	PlayerWeaponsArray[WeaponType].WeaponInfo = Weapon->WeaponStats;
}

void UWeaponComponentCpp::SaveStatsInWeapon(AWeaponActorCpp* DroppedWeapon)
{
	if(IsValid(DroppedWeapon))
	{
		EWeaponTypeC WeaponType = DroppedWeapon->WeaponType;
		DroppedWeapon->WeaponStats = PlayerWeaponsArray[WeaponType].WeaponInfo;
	}
}

void UWeaponComponentCpp::NewRound_Implementation()
{
	for (int i = 0; i < 6; i++)
	{
		if(IsValid(PlayerWeaponsArray[i].Weapon))
		{
			PlayerWeaponsArray[i].WeaponInfo.CurrentAmmo = PlayerWeaponsArray[i].WeaponInfo.MaxAmmoInClip;
		}
	}

	if (IsValid(CurrentWeapon))
	{
		SaveStatsInWeapon(CurrentWeapon);
		NeedUpdateWidget();
	}
		
}


void UWeaponComponentCpp::EndFireServer_Implementation()
{
	if (CanFire)
	{
		if (IsValid(CurrentWeapon))
			CurrentWeapon->EndFire();
	}
}

void UWeaponComponentCpp::StartFireServer_Implementation()
{
	if (CanFire)
	{
		if (IsValid(CurrentWeapon))
			CurrentWeapon->StartFire();
	}
}


void UWeaponComponentCpp::SwapWeapon_Implementation(EWeaponTypeC WeaponType)
{
	if(IsValid(CurrentWeapon))
	{
		SaveWeaponToSlot(CurrentWeapon);
		CurrentWeapon->Destroy();

		PreAttachWeapon(WeaponType);
	}
	else
	{
		PreAttachWeapon(WeaponType);
	}
}





void UWeaponComponentCpp::TryToSelectWeapon_Implementation(EWeaponTypeC WeaponType)
{
	if(SlotValid(WeaponType))
	{
		if(CurrentWeapon->WeaponType != WeaponType)
		{
			SwapWeapon(WeaponType);
		}
		
	}
}





void UWeaponComponentCpp::SelectValidSlot_Implementation()
{
	for (int i = 0; i < 6; i++)
	{
		if (SlotValid(StaticCast<EWeaponTypeC>(i)))
		{
			PreAttachWeapon(i);
			break;
		}
	}
}






void UWeaponComponentCpp::RemoveWeaponFromSlot_Implementation(int WeaponSlot)
{
	FPlayerWeaponC Empty;
	PlayerWeaponsArray[WeaponSlot] = Empty;
	NeedUpdateWidget();
}






void UWeaponComponentCpp::DropWeapon_Implementation(EWeaponTypeC WeaponType)
{
	FPlayerWeaponC LWeapon = PlayerWeaponsArray[WeaponType];
	if(IsValid(LWeapon.Weapon))
	{
		FActorSpawnParameters SpawnParameters;

		FVector DropLocation = OwnerRef->GetActorLocation();
		DropLocation += OwnerRef->GetActorForwardVector() * 100;

		FRotator DropRotation = OwnerRef->GetActorRotation();

		AWeaponActorCpp* DroppedWeapon = GetWorld()->SpawnActor<AWeaponActorCpp>(LWeapon.Weapon, DropLocation, DropRotation, SpawnParameters);

		SaveWeaponToSlot(CurrentWeapon);
		SaveStatsInWeapon(DroppedWeapon);

		if (WeaponType == CurrentWeapon->WeaponType)
		{
			CurrentWeapon->Destroy();
		}

		RemoveWeaponFromSlot(WeaponType);
	}
	

}






void UWeaponComponentCpp::AttachWeaponMulticast_Implementation(AWeaponActorCpp* Weapon)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %i,"), IsValid(Weapon)));
	if(IsValid(Weapon))
	{
		UMeshComponent* Mesh = Weapon->WeaponMesh;
		
		DisableCollision(Weapon);
		Mesh->AttachToComponent(OwnerRef->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Weapon->WeaponSocket.ActiveSocket);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
		
	}


}








void UWeaponComponentCpp::PreAttachWeapon_Implementation(int WeaponSlot)
{
	FPlayerWeaponC LWeapon = PlayerWeaponsArray[WeaponSlot];
	if(IsValid(LWeapon.Weapon))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = OwnerRef;

		CurrentWeapon = GetWorld()->SpawnActor<AWeaponActorCpp>(LWeapon.Weapon, FVector(), FRotator(), SpawnParameters);
		CurrentWeapon->CurrentPlayer = OwnerRef;
		CurrentWeapon->WeaponStats = LWeapon.WeaponInfo;

		OnCurrentWeaponChanges();
		//AttachWeaponMulticast(CurrentWeapon);
	}
	
}





void UWeaponComponentCpp::AddWeaponAuto_Implementation(AWeaponActorCpp* Weapon)
{
	if (IsValid(Weapon))
	{
		TEnumAsByte<EWeaponTypeC> LWeaponType = Weapon->WeaponType;
		//FPlayerWeaponC PlayerWeapon = PlayerWeaponsArray[static_cast<int>(LWeaponType)];

		if (SlotValid(LWeaponType) == false)
		{
			SaveWeaponToSlot(Weapon);

			if (IsValid(CurrentWeapon) == false)
			{
				PreAttachWeapon(LWeaponType);
			}
			Weapon->Destroy();
		}
	}
}







void UWeaponComponentCpp::AddWeaponManual_Implementation(AWeaponActorCpp* Weapon)
{
	if (IsValid(Weapon))
	{
		FWeaponStatsC LWeaponStats = Weapon->WeaponStats;
		TEnumAsByte<EWeaponTypeC> LWeaponType = Weapon->WeaponType;
		int WeaponSlot = static_cast<int>(LWeaponType);
		FPlayerWeaponC PlayerWeapon = PlayerWeaponsArray[static_cast<int>(LWeaponType)];

		if (SlotValid(LWeaponType))
		{
			if (IsValid(CurrentWeapon))
			{
				SaveWeaponToSlot(Weapon);

				CurrentWeapon->Destroy();
			}

			DropWeapon(LWeaponType);

			SaveWeaponToSlot(Weapon);

			PreAttachWeapon(WeaponSlot);

			Weapon->Destroy();

		}
		else
		{
			SaveWeaponToSlot(Weapon);

			Weapon->Destroy();

			if (IsValid(CurrentWeapon) == false)
			{
				PreAttachWeapon(WeaponSlot);
			}
			else
			{
				SwapWeapon(LWeaponType);
			}

		}
	}
}

void UWeaponComponentCpp::NeedUpdateWidget_Implementation()
{
	OwnerRef->NeedUpdateWidgetAmmo();
}

