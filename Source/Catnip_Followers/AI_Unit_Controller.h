// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIData.h"

#include "AI_Unit_Controller.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReachedDestinationDelegate, const FCommandData, CommandData);

class ACatnip_FollowersCharacter;

UCLASS()
class CATNIP_FOLLOWERS_API AAI_Unit_Controller : public AAIController
{
	GENERATED_BODY()
public:
	AAI_Unit_Controller(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void CommandMove(FCommandData CommandData);

	UPROPERTY()
	FReachedDestinationDelegate OnReachedDestination;

protected:
	virtual void OnPossess(class APawn* InPawn) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;


	UPROPERTY()
	ACatnip_FollowersCharacter* OwningCharacter;

	UPROPERTY()
	FCommandData CurrentCommandData;
	
};
