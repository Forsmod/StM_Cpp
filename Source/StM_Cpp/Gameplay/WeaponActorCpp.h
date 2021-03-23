// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ST_WEaponSocket.h"
#include "ST_WeaponStats.h"
#include "EWeaponTypeCpp.h"
#include "Components/CapsuleComponent.h"
#include "StM_Cpp/Gameplay/Characters/GameplayCharacterCpp.h"

#include "WeaponActorCpp.generated.h"



UCLASS()
class STM_CPP_API AWeaponActorCpp : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AWeaponActorCpp();


	UPROPERTY(BlueprintReadWrite)
		USceneComponent* Scene;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UCapsuleComponent* CapsuleCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* WeaponMesh;

	UPROPERTY(BlueprintReadWrite, Replicated)
		AGameplayCharacterCpp* CurrentPlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, ReplicatedUsing = NeedUpdateWidget)
		FWeaponStatsC WeaponStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FWeaponSocketC WeaponSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TEnumAsByte<EWeaponTypeC> WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int Cost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float Damage;
	
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Server, Reliable)
		virtual void StartFire();

	UFUNCTION(BlueprintCallable, Server, Reliable)
		virtual void EndFire();

	UFUNCTION()
		void NeedUpdateWidget();
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};




