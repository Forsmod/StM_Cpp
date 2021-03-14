// Fill out your copyright notice in the Description page of Project Settings.

#include "MainComponentCpp.h"
#include "GameFramework/Character.h"


// Sets default values for this component's properties
UMainComponentCpp::UMainComponentCpp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	SetIsReplicated(true);
}


// Called when the game starts
void UMainComponentCpp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OwnerRef = Cast<ACharacter>(GetOwner());
}


// Called every frame
void UMainComponentCpp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

