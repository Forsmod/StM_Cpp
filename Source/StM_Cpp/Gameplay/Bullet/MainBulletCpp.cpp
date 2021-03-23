// Fill out your copyright notice in the Description page of Project Settings.


#include "MainBulletCpp.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AMainBulletCpp::AMainBulletCpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	
	BulletMesh->SetupAttachment(BoxCollision);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->InitialSpeed = 10000;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMainBulletCpp::OnBoxCollisionBeginOverlap);

	BoxCollision->OnComponentHit.AddDynamic(this, &AMainBulletCpp::OnBoxHit);

}

void AMainBulletCpp::DestroyBullet()
{
	Destroy();
}

void AMainBulletCpp::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (GetInstigator()->GetClass() != OtherActor->GetClass())
	{
		if (OtherActor != GetOwner())
		{
			if (UKismetSystemLibrary::IsServer(GetWorld()))
			{
				UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigator()->GetController(), GetInstigator(), 0);
			}
			
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterBlood, SweepResult.Location, FRotator::ZeroRotator, FVector(0.5), true, EPSCPoolMethod::None, true);
			Destroy();
		}
	}
}

void AMainBulletCpp::OnBoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}

// Called when the game starts or when spawned
void AMainBulletCpp::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &AMainBulletCpp::DestroyBullet, 5, false, -1);
	
}

// Called every frame
void AMainBulletCpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

