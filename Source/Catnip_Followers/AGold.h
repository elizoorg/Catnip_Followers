// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIData.h"
#include "AResource.h"
#include "Usable.h"
#include "AGold.generated.h"

/**
 * 
 */
UCLASS()
class CATNIP_FOLLOWERS_API AAGold : public AAResource,public IUsable
{
	GENERATED_BODY()
public:
	AAGold();

	virtual ECommandType Use() override;
	
};
