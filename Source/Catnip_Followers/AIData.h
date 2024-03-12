﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIData.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECommandType
{
	WAIT,
	MOVE,
	ATTACK,
	GATHER
};

USTRUCT(BlueprintType)
struct FCommandData
{
	GENERATED_BODY()
public:
	FCommandData() : Location(FVector::ZeroVector), Rotation(FRotator::ZeroRotator), Type(ECommandType::MOVE), Target(nullptr){}
	FCommandData(const FVector InLocation, const FRotator InRotation, const ECommandType InType,AActor* InTarget = nullptr):
	Location(InLocation),Rotation(InRotation),Type(InType),Target(InTarget){}

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector Location;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FRotator Rotation;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<ECommandType> Type;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* Target;
};


