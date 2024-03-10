// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums.h"
#include "ResourceInterface.h"
#include "AResource.generated.h"



USTRUCT()
struct FResource
{
	GENERATED_BODY()
public:
	EResourse Resource;
};

UCLASS()
class CATNIP_FOLLOWERS_API AAResource : public AActor,public IResourceInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAResource();
	
protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	FResourceStats stats;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void TakeResources(int32 amount) override;
	virtual EResourse GetType() override;
	virtual int32 GetAmount() override;

};
