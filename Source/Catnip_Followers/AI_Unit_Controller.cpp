// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Unit_Controller.h"
#include "Catnip_FollowersCharacter.h"
#include "ResourceInterface.h"
#include <Components/BoxComponent.h>

#include "Convertable.h"
#include "Kismet/GameplayStatics.h"


#define MIN(a,b) (a < b) ? (a) : (b)
#define MAX(a,b) (a > b) ? (a) : (b)


AAI_Unit_Controller::AAI_Unit_Controller(const FObjectInitializer& ObjectInitializer)
{
	selectionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("selectionArea"));
	selectionArea->SetBoxExtent(FVector(1500, 1500, 1000));


}

void AAI_Unit_Controller::CommandMove(FCommandData CommandData)
{
	CurrentCommandData = CommandData;
	MoveToLocation(CommandData.Location);
}

void AAI_Unit_Controller::CommandGather(FCommandData CommandData)
{

	CurrentCommandData = CommandData;
	Gathering();
}

void AAI_Unit_Controller::CommandDeposit(FCommandData CommandData)
{
	CurrentCommandData = CommandData;
	Deposit();

}

void AAI_Unit_Controller::CommandConvert(FCommandData CommandData)
{
	CurrentCommandData = CommandData;
	Convert();
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

void AAI_Unit_Controller::Gathering()
{
	IResourceInterface* ri = Cast<IResourceInterface>(CurrentCommandData.Target);
	int32 amount = ri->GetAmount();
	int32 space = OwningCharacter->GetCarryWeight() - OwningCharacter->GetWeight();
	if (amount > 0) {
		// Do we have carry space left
		if (space > 0) {
			// Find the lowest amount to gather, either the resources has less than we can carry / gather or we lack the space to gather fully
			int32 amountToTake = MIN(amount, space);
			amountToTake = MIN(OwningCharacter->GetGatherAmount(), amountToTake);

			ri->TakeResources(amountToTake);
			OwningCharacter->RecieveResources(amountToTake, ri);
		}
		// We ran out of space so return to storage
		else {
			CurrentCommandData.Type = ECommandType::DEPOSIT;
		}
	}
	// The target ran out of resources, but we still have carry space
	else if (space > 0) {
		TArray<AActor*> resourceActors;

		GetNearbyActors(resourceActors);
		ShuffleArray<AActor*>(resourceActors);

		bool resFound = FindResource(ri->GetType(), resourceActors);

		if (resourceActors.Num() == 0 || !resFound) {
			CurrentCommandData.Type = ECommandType::DEPOSIT;
		}
	}
	// We ran out of space so return to storage
	else {
		CurrentCommandData.Type = ECommandType::DEPOSIT;
	}
	OnGatheringDone.Broadcast(CurrentCommandData);
}

void AAI_Unit_Controller::Deposit()
{

	AActor* previousTarget = CurrentCommandData.Target;

	if (!CurrentCommandData.Target->Implements<UStorageInterface>()) {
		TArray<AActor*> storageActors;
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UStorageInterface::StaticClass(), storageActors);

		for (AActor* store : storageActors) {
				CurrentCommandData.Target=store;
		}
	}
	else {
		IStorageInterface* storage = Cast<IStorageInterface>(CurrentCommandData.Target);

		for (FItem& item : OwningCharacter->GetStats().inventory.items) {
			storage->AddItem(item.itemName, item.amount);
		}

		OwningCharacter->ClearInventory();

		if (previousTarget->Implements<UResourceInterface>()) {
			CurrentCommandData.Target=previousTarget;
			CurrentCommandData.Type = ECommandType::GATHER;
		}
	}
	OnDepositDone.Broadcast(CurrentCommandData);
}

void AAI_Unit_Controller::Convert()
{
	IConvertable* conv = Cast<IConvertable>(CurrentCommandData.Target);
	IStorageInterface* storage = Cast<IStorageInterface>(CurrentCommandData.Target);
	FResourceStats from = conv->ToConvert();
	FResourceStats to = conv->FromConvert();
	if (OwningCharacter->GiveResources(from.amount,from))
	{
		OwningCharacter->RecieveResources(to);
	}
	OnConvertDone.Broadcast(CurrentCommandData);
}


void AAI_Unit_Controller::GetNearbyActors(TArray<AActor*>& actors)
{
	selectionArea->SetWorldLocation(OwningCharacter->GetActorLocation());
	selectionArea->GetOverlappingActors(actors);
}

bool AAI_Unit_Controller::FindResource(EResourse resType, TArray<AActor*> actors)
{
	bool resFound = false;

	for (AActor* res : actors) {
		IResourceInterface* resi = Cast<IResourceInterface>(res);

		if (resi != NULL && resi->GetType() == resType && resi->GetAmount() > 0 && !res->IsUnreachable()) {
			// Is this resource that can be attacked?
			/*if (res->Implements<UDamagableInterface>()) {
				IDamagableInterface* damagei = Cast<IDamagableInterface>(res);

				// Does the target have health left?
				if (damagei->GetHealth() > 0) {
					// Attack the target
					CurrentCommandData.Target = res;
					resFound = true;
					CurrentCommandData.Type = ECommandType::ATTACK;
					break;
				}
				// They're dead, so gather from it
				else {
					CurrentCommandData.Target = res;
					resFound = true;
					break;
				}
			}
			// They can't be attacked, so gather from it
			else {*/
				CurrentCommandData.Target= res;
				resFound = true;
				break;
			
		}
	}

	return resFound;
}

bool AAI_Unit_Controller::IsCloseEnough(FCommandData CommandData)
{
	return FVector::Dist(OwningCharacter->GetActorLocation(), CommandData.Target->GetActorLocation()) < 200.0f; // Assuming 100 units is close enough

}

void AAI_Unit_Controller::DelayedExecute(float DelayTime, FCommandData CommandData)
{
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;
	switch(CommandData.Type)
	{
	case ECommandType::DEPOSIT:
		TimerDel = FTimerDelegate::CreateUObject(this, &ThisClass::CommandDeposit, CommandData);
		break;
	case ECommandType::MOVE:
		TimerDel = FTimerDelegate::CreateUObject(this, &ThisClass::CommandMove, CommandData);
		break;
	case ECommandType::GATHER:
		TimerDel = FTimerDelegate::CreateUObject(this, &ThisClass::CommandGather, CommandData);
		break;
	case ECommandType::CONVERT:
		TimerDel = FTimerDelegate::CreateUObject(this, &ThisClass::CommandConvert, CommandData);
		break;
	default:
		break;
	}
	 

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, DelayTime, false);
}
