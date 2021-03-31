// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActorCpp.h"

#include "WeaponComponentCpp.h"
#include "Kismet/KismetMathLibrary.h"
#include "StM_Cpp/Gameplay/Characters/GameplayCharacterCpp.h"

// Sets default values
AWeaponActorCpp::AWeaponActorCpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	
	WeaponMesh->SetupAttachment(CapsuleCollision);
	CapsuleCollision->SetupAttachment(Scene);
	RootComponent = Scene;
	
	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponActorCpp::OnOverlapBegin);
	CapsuleCollision->SetSimulatePhysics(true);
	
}

void AWeaponActorCpp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AWeaponActorCpp, CurrentPlayer, COND_None);
	DOREPLIFETIME_CONDITION(AWeaponActorCpp, WeaponStats, COND_OwnerOnly);

}

void AWeaponActorCpp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(HasAuthority())
	{
		AGameplayCharacterCpp *Character = Cast<AGameplayCharacterCpp>(OtherActor);
		if(IsValid(Character))
		{
			Character->WeaponComponent->AddWeaponAuto(this);
		}
		
	}
}

void AWeaponActorCpp::StartFire_Implementation()
{
	
}

void AWeaponActorCpp::EndFire_Implementation()
{
	
}

void AWeaponActorCpp::NeedUpdateWidget()
{
	if(IsValid(CurrentPlayer))
	{
		CurrentPlayer->NeedUpdateWidgetAmmo();
	}
}

void AWeaponActorCpp::Dropped_Implementation()
{
	GetWorldTimerManager().SetTimer(SynchMoveTimer, this, &AWeaponActorCpp::PhysicsTick, 0.2, true, -1);
}

void AWeaponActorCpp::PhysicsTick()
{
	FVector SyncVelocity = CapsuleCollision->GetPhysicsLinearVelocity();
	FTransform SyncTransform = CapsuleCollision->GetComponentTransform();
	
	SynchronizeMove(SyncTransform, SyncVelocity);

	if (UKismetMathLibrary::EqualEqual_VectorVector(SyncTransform.GetLocation(), OldPosotion, 0.1))
	{
		GetWorldTimerManager().ClearTimer(SynchMoveTimer);
		DisablePhysics();

	}
	else
	{
		OldPosotion = CapsuleCollision->GetComponentLocation();
	}
}

void AWeaponActorCpp::SynchronizeMove_Implementation(FTransform Transform, FVector Velocity)
{
	CapsuleCollision->SetWorldTransform(Transform);
	CapsuleCollision->SetPhysicsLinearVelocity(Velocity);
}

void AWeaponActorCpp::DisablePhysics_Implementation()
{
	CapsuleCollision->SetSimulatePhysics(false);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Stop Sync"));
}

// Called when the game starts or when spawned
void AWeaponActorCpp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponActorCpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


