// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceInterface.h"


FString IResourceInterface::GetEnumName()
{
	return UEnums::EnumToString(TEXT("EResourceType"), static_cast<uint8>(GetType()));
}

void IResourceInterface::TakeResources(int32 amount)
{

}

EResourse IResourceInterface::GetType()
{
	return EResourse::Food;
}

int32 IResourceInterface::GetAmount()
{
	return 0;
}

// Add default functionality here for any IResourceInterface functions that are not pure virtual.
