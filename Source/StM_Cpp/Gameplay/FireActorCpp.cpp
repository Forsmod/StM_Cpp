// Fill out your copyright notice in the Description page of Project Settings.


#include "FireActorCpp.h"

#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

void AFireActorCpp::BeginPlay()
{
	AWeaponActorCpp::BeginPlay();
	AttackSpeed = 1. / AttackSpeedPerSec;
}

AFireActorCpp::AFireActorCpp()
{
	BulletStart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletStart"));
	BulletStart->SetupAttachment(WeaponMesh);
}


void AFireActorCpp::StartFire()
{
	SetFire = true;
	if(GetWorldTimerManager().TimerExists(SecondFire) == false)
	{
		GetWorldTimerManager().SetTimer(SecondFire, this, &AFireActorCpp::EndTimeSecondFire, AttackSpeed, false, -1);
		Loop();
	}
	
}

void AFireActorCpp::EndTimeSecondFire()
{
	GetWorldTimerManager().ClearTimer(SecondFire);
}



void AFireActorCpp::SpawnBulletMulticast_Implementation(FTransform Transform)
{
	FVector BulletStartLocation = BulletStart->GetComponentLocation();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = CurrentPlayer;
	SpawnParameters.Owner = this;
	
	AMainBulletCpp *Bullet = GetWorld()->SpawnActor<AMainBulletCpp>(BulletClass, BulletStartLocation, Transform.Rotator(), SpawnParameters);
	Bullet->Damage = Damage;
}


void AFireActorCpp::EndFire()
{
	SetFire = false;
	Loop();
}



void AFireActorCpp::Loop()
{
	if(SetFire & (IsReload == false))
	{
		GetWorldTimerManager().SetTimer(LoopFireHandle, this, &AFireActorCpp::TryShoot, AttackSpeed, AutomaticFire, 0);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(LoopFireHandle);
	}
}

void AFireActorCpp::TryShoot()
{
	if (WeaponStats.CurrentAmmo <= 0)
	{
		StartReload();
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Ammoo: %i"), WeaponStats.CurrentAmmo));
		FVector CameraLocation = CurrentPlayer->GetFollowCamera()->GetComponentLocation();
		FVector CameraForwardVector = CurrentPlayer->GetFollowCamera()->GetForwardVector();
		FVector EndLocation = CameraForwardVector * 10000 + CameraLocation;

		FHitResult Hit;

		FCollisionQueryParams MyParams;
		
		if (GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, EndLocation, ECC_Visibility, MyParams, FCollisionResponseParams::DefaultResponseParam))
		{
			SpawnBulletMulticast(FindBulletTransform(Hit.ImpactPoint));
			//DrawDebugLine(GetWorld(), CameraLocation, Hit.Location, FColor(255, 0, 0), false, 5, 0, 0.5);
		}
		else
		{
			SpawnBulletMulticast(FindBulletTransform(EndLocation));
		}
		WeaponStats.CurrentAmmo--;
		NeedUpdateWidget();
	}
		
}

void AFireActorCpp::StartReload_Implementation()
{
	if (IsReload == false)
	{
		GetWorldTimerManager().SetTimer(ReloadHandle, this, &AFireActorCpp::EndReload, ReloadTime, false, -1);
		IsReload = true;
	}
}


void AFireActorCpp::EndReload()
{
	IsReload = false;
	WeaponStats.CurrentAmmo = WeaponStats.MaxAmmoInClip;
	NeedUpdateWidget();
}

FTransform AFireActorCpp::FindBulletTransform(FVector Target)
{
	FVector BulletStartLocation = BulletStart->GetComponentLocation();
	FRotator BulletRotation = UKismetMathLibrary::FindLookAtRotation(BulletStartLocation, Target);

	FTransform BulletTransform = UKismetMathLibrary::MakeTransform(BulletStartLocation, BulletRotation, FVector(1, 1, 1));

	return BulletTransform;
}
