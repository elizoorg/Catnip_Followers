// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskManager.h"
#include "Stock.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATaskManager::ATaskManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ATaskManager::BeginPlay()
{
	Super::BeginPlay();

	TArray <AActor*> storageActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UStorageInterface::StaticClass(), storageActors);

	for (AActor* store : storageActors) {
		stock = Cast<AStock>(store);
		if (stock) break;
	}

	stock->inventoryChange.AddDynamic(this, &ATaskManager::InventoryChanged);
	
}

void ATaskManager::InventoryChanged(FInventory newInventory)
{
	FTask thistask = tasks[currenttask];
	bool isDone = true;
	for(FResourceStats stats:thistask.Thistems)
	{
		FString str = UEnums::EnumToString(TEXT("EResourse"), static_cast<uint8>(stats.resourceType));
		FItem  *Item = newInventory.FindItem(str);
		if(Item->amount < stats.amount)
		{
			isDone = false;
		}
		

	}
	if (isDone) {
		currenttask++;

		UE_LOG(LogTemp, Warning, TEXT("We're end one o the task, congrats"));
	}
	
}


