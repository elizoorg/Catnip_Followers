// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums.h"
#include "Convertable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UConvertable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CATNIP_FOLLOWERS_API IConvertable
{
	GENERATED_BODY()

protected:
	

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FResourceStats ToConvert() = 0;
	virtual FResourceStats FromConvert() = 0;
};
