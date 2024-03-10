// Copyright Epic Games, Inc. All Rights Reserved.

#include "Catnip_FollowersGameMode.h"
#include "Catnip_FollowersPlayerController.h"
#include "Catnip_FollowersCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACatnip_FollowersGameMode::ACatnip_FollowersGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACatnip_FollowersPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}