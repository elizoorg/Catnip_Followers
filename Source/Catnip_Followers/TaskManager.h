// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "GameFramework/Actor.h"
#include "TaskManager.generated.h"


USTRUCT(BlueprintType)
struct FTask
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	TArray <FResourceStats> Thistems;
private:

	


};


class AStock;


UCLASS()
class CATNIP_FOLLOWERS_API ATaskManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATaskManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	AStock* stock;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	TArray<FTask> tasks;
	// Called every frame

	UFUNCTION(BlueprintCallable, Category = "Tasks")
	void InventoryChanged(FInventory newInventory);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	int taskcount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	int currenttask = 0;


};
