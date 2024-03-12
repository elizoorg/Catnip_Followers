// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Unit_Controller.h"
#include "Catnip_FollowersCharacter.h"

AAI_Unit_Controller::AAI_Unit_Controller(const FObjectInitializer& ObjectInitializer)
{
}

void AAI_Unit_Controller::CommandMove(FCommandData CommandData)
{
	CurrentCommandData = CommandData;
	MoveToLocation(CommandData.Location);
}

void AAI_Unit_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwningCharacter = Cast<ACatnip_FollowersCharacter>(InPawn);
	if(OwningCharacter)
	{
		OwningCharacter->SetAIController(this);
	}
}

void AAI_Unit_Controller::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	OnReachedDestination.Broadcast(CurrentCommandData);
}
