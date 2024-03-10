// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums.h"
#include "ResourceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UResourceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CATNIP_FOLLOWERS_API IResourceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FString GetEnumName();
	virtual void TakeResources(int32 amount);
	virtual EResourse GetType();
	virtual int32 GetAmount();
};
