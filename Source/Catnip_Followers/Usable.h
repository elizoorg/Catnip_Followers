// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIData.h"
#include "UObject/Interface.h"
#include "Usable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UUsable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CATNIP_FOLLOWERS_API IUsable
{
	GENERATED_BODY()
public:
	virtual ECommandType Use() = 0;

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
