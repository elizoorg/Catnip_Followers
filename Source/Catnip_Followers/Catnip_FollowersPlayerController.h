// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Catnip_FollowersPlayerController.generated.h"

class AAI_Unit_Controller;
/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ACatnip_FollowersPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACatnip_FollowersPlayerController();
	UFUNCTION()
	void Handle_Selection(AActor* ActorToSelect);
	UFUNCTION()
	bool ActorSelected(AActor* ActorToCheck);

	

protected:
	
	

private:

};


