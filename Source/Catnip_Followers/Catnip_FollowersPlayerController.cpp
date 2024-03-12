// Copyright Epic Games, Inc. All Rights Reserved.

#include "Catnip_FollowersPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Catnip_FollowersCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

ACatnip_FollowersPlayerController::ACatnip_FollowersPlayerController()
{
	bShowMouseCursor = true;
}

void ACatnip_FollowersPlayerController::Handle_Selection(AActor* ActorToSelect)
{
	if(ISelectable* Selectable = Cast<ISelectable>(ActorToSelect))
	{
		if(ActorToSelect && ActorSelected(ActorToSelect))
		{

		}
		else
		{
			
		}
	}
}

bool ACatnip_FollowersPlayerController::ActorSelected(AActor* ActorToCheck)
{
	if(ActorToCheck)
	{
		return true;
	}
	return false;
}
