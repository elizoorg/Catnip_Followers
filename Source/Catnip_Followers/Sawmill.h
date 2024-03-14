// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AResource.h"
#include "Building.h"
#include "Convertable.h"
#include "Selectable.h"
#include "Usable.h"
#include "GameFramework/Actor.h"
#include "Sawmill.generated.h"


UCLASS()
class CATNIP_FOLLOWERS_API ASawmill : public ABuilding,public IConvertable,public ISelectable,public IUsable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASawmill();


	virtual  void Select() override;
	virtual  void DeSelect() override;
	virtual  void HighLight(const bool Highlight) override;
	virtual ECommandType Use() override;
	virtual  FResourceStats FromConvert() override;
	virtual  FResourceStats ToConvert() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	FResourceStats toConvert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	FResourceStats fromConvert;


	UPROPERTY()
	bool Selected;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
