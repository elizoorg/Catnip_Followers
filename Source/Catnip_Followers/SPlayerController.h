// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIData.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CATNIP_FOLLOWERS_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASPlayerController();


	UFUNCTION()
	void Handle_Selection(AActor* ActorToSelect);
	UFUNCTION()
	bool ActorSelected(AActor* ActorToCheck) const;
	UFUNCTION()
	void Select(AActor* ActorToSelect);
	UFUNCTION()
	void DeSelect(AActor* ActorToDeSelect);

	UFUNCTION()
	void ClearSelected();

	UFUNCTION()
	void CommandSelected(FCommandData CommandData);



	UPROPERTY()
	TArray<AActor*> Selected;
};


