// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIData.h"
#include "Building.h"
#include "Selectable.h"
#include "StorageInterface.h"
#include "Usable.h"
#include "Stock.generated.h"

/**
 * 
 */
UCLASS()
class CATNIP_FOLLOWERS_API AStock : public ABuilding, public IStorageInterface, public ISelectable, public IUsable
{
	GENERATED_BODY()
public:
	AStock();


	virtual  void Select() override;
	virtual  void DeSelect() override;
	virtual  void HighLight(const bool Highlight) override;
	virtual ECommandType Use() override;

	UPROPERTY()
	bool Selected;


};
