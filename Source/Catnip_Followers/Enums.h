// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"


UENUM()
enum class EResourse : uint8
{
	Wood,
	Stone,
	Gold,
	Food
};


USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString itemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 amount;
};

USTRUCT(BlueprintType)
struct FResourceStats
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float  amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	EResourse resourceType;
};


USTRUCT(BlueprintType)
struct FInventory
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<FItem> items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 capacity;

	FItem* FindItem(FString itemName) {
		for (FItem& item : items) {
			if (item.itemName.Equals(itemName)) {
				return &item;
			}
		}
		return NULL;
	}
};


UCLASS()
class CATNIP_FOLLOWERS_API UEnums : public UObject
{
	GENERATED_BODY()
public:

	FORCEINLINE static const FString EnumToString(const TCHAR* Enum, int32 EnumValue)
	{
		const UEnum* EnumPtr = FindFirstObjectSafe<UEnum>(Enum);
		if (!EnumPtr)
			return NSLOCTEXT("Invalid", "Invalid", "Invalid").ToString();

#if WITH_EDITOR
		return EnumPtr->GetDisplayNameTextByValue(EnumValue).ToString();
#else
		return EnumPtr->GetEnumName(EnumValue);
#endif
	}
};