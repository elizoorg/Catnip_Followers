// Fill out your copyright notice in the Description page of Project Settings.


#include "AResource.h"

// Sets default values
AAResource::AAResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



// Called every frame
void AAResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAResource::TakeResources(int32 amount)
{
	stats.amount -= amount;

	if (stats.amount <= 0) {
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}

EResourse AAResource::GetType()
{
	return stats.resourceType;
}

int32 AAResource::GetAmount()
{
	return stats.amount;
}

