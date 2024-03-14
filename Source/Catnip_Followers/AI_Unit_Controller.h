// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIData.h"

#include "Enums.h"
#include "Components/BoxComponent.h"
#include "AI_Unit_Controller.generated.h"



/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReachedDestinationDelegate, const FCommandData, CommandData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGatheringIsDone, const FCommandData, CommandData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDepositIsDone, const FCommandData, CommandData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConvertIsDone, const FCommandData, CommandData);

class ACatnip_FollowersCharacter;

UCLASS()
class CATNIP_FOLLOWERS_API AAI_Unit_Controller : public AAIController
{
	GENERATED_BODY()
public:
	AAI_Unit_Controller(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void CommandMove(FCommandData CommandData);

	UFUNCTION()
	void CommandGather(FCommandData CommandData);

	UFUNCTION()
	void CommandDeposit(FCommandData CommandData);

	UFUNCTION()
	void CommandConvert(FCommandData CommandData);

	UFUNCTION()
	bool IsCloseEnough(FCommandData CommandData);

	UFUNCTION()
	void DelayedExecute(float DelayTime,FCommandData CommandData);

	UPROPERTY()
	FReachedDestinationDelegate OnReachedDestination;

	UPROPERTY()
	FGatheringIsDone OnGatheringDone;

	UPROPERTY()
	FGatheringIsDone OnDepositDone;

	UPROPERTY()
	FConvertIsDone OnConvertDone;

	UPROPERTY()
	FCommandData CurrentCommandData;

protected:
	virtual void OnPossess(class APawn* InPawn) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;

	UFUNCTION()
	void Gathering();

	UFUNCTION()
	void Deposit();

	UFUNCTION()
	void Convert();

	UFUNCTION()
	void GetNearbyActors(TArray<AActor*>& actors);

	UPROPERTY()
	UBoxComponent* selectionArea;

	UPROPERTY()
	ACatnip_FollowersCharacter* OwningCharacter;





	template <class T> static void ShuffleArray(TArray<T>& arrayIn);

	UFUNCTION()
	bool FindResource(EResourse resType, TArray<AActor*> actors);


	
};

template <class T>
void AAI_Unit_Controller::ShuffleArray(TArray<T>& arrayIn)
{
	if (arrayIn.Num() > 0)
	{
		int32 LastIndex = arrayIn.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index)
			{
				arrayIn.Swap(i, Index);
			}
		}
	}
}