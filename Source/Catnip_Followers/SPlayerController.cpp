// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerController.h"

#include "Catnip_FollowersCharacter.h"
#include "Selectable.h"

ASPlayerController::ASPlayerController()
{
	bShowMouseCursor = true;
}

void ASPlayerController::Handle_Selection(AActor* ActorToSelect)
{
	UE_LOG(LogTemp, Warning, TEXT("Hello World3"));
	if (ISelectable* Selectable = Cast<ISelectable>(ActorToSelect))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hello World4"));
		if (ActorToSelect && ActorSelected(ActorToSelect))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hello World5"));
			DeSelect(ActorToSelect);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Hello World9"));
			Select(ActorToSelect);
		}
	}
}

bool ASPlayerController::ActorSelected(AActor* ActorToCheck) const
{
	if(ActorToCheck && Selected.Contains(ActorToCheck))
	{
		return true;
	}
	return false;
}




void ASPlayerController::Select(AActor* ActorToSelect)
{
	UE_LOG(LogTemp, Warning, TEXT("Hello 6"));
	ClearSelected();
	if(ActorToSelect)
	{
		if(ISelectable* Selectable = Cast<ISelectable>(ActorToSelect))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hello World7"));
			Selectable->Select();
			Selected.Add(ActorToSelect);
		}
	}
}

void ASPlayerController::DeSelect(AActor* ActorToDeSelect)
{
	if (ActorToDeSelect)
	{
		if (ISelectable* Selectable = Cast<ISelectable>(ActorToDeSelect))
		{
			Selectable->DeSelect();
			Selected.Remove(ActorToDeSelect);
		}
	}
}

void ASPlayerController::ClearSelected()
{
	for(int i = 0 ; i < Selected.Num(); ++i)
	{
		if(Selected[i])
		{
			if(ISelectable * Selectable = Cast<ISelectable>(Selected[i]))
			{
				Selectable->DeSelect();
			}
		}
	}
	Selected.Empty();
}

void ASPlayerController::CommandSelected(FCommandData CommandData)
{
	for (int i = 0; i < Selected.Num(); ++i)
	{
		if (ACatnip_FollowersCharacter* SelectedCharacter = Cast<ACatnip_FollowersCharacter>(Selected[i]))
		{
			SelectedCharacter->CommandMove(CommandData);
		}
	}
}




