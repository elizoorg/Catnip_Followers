// Copyright Epic Games, Inc. All Rights Reserved.

#include "Catnip_FollowersCharacter.h"

#include "AI_Unit_Controller.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "ResourceInterface.h"

ACatnip_FollowersCharacter::ACatnip_FollowersCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	stats.currentHealth = 100;
	stats.maxHealth = 100;
	stats.inventory.capacity = 100;
	stats.gatherAmount = 5;
	stats.unitName = "Character";


	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = SkeletalMeshComponent;


	AIControllerClass = AAI_Unit_Controller::StaticClass();
}

void ACatnip_FollowersCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);


	if(ShouldOrientate)
	{
		SetOrientation(DeltaSeconds);

		if(IsOrientated())
		{
			ShouldOrientate = 0;
		}
	}

	
}

void ACatnip_FollowersCharacter::Select()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello World okay"));

	Selected = true;
	HighLight(Selected);
}

void ACatnip_FollowersCharacter::DeSelect()
{
	Selected = false;
	HighLight(Selected);
}

void ACatnip_FollowersCharacter::HighLight(const bool Highlight)
{
	UE_LOG(LogTemp, Warning, TEXT("Hello World lol"));

	TArray<UPrimitiveComponent*> Components;
	GetComponents<UPrimitiveComponent>(Components);
	for(UPrimitiveComponent* VisualComp: Components)
	{
		if(UPrimitiveComponent* Prim = Cast <UPrimitiveComponent>(VisualComp))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hello World xdd"));

			Prim->SetRenderCustomDepth(Highlight);
		}
	}

}

void ACatnip_FollowersCharacter::SetOrientation(const float DeltaTime)
{
	const FRotator InterpolatedRotation = UKismetMathLibrary::RInterpTo(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 0.f), TargetOrientation, DeltaTime, 2.f);
	SetActorRotation(InterpolatedRotation);
}

bool ACatnip_FollowersCharacter::IsOrientated() const
{
	const FRotator CurrentRotation = GetActorRotation();
	if (FMath::IsNearlyEqual(CurrentRotation.Yaw, TargetOrientation.Yaw, 0.25f))
	{
		return true;
	}
	return false;
}

void ACatnip_FollowersCharacter::CommandMove(const FCommandData CommandData)
{
	if(!SAIController)
	{
		return;
	}
	IsCommandDone = false;
	SAIController->OnReachedDestination.Clear();
	SAIController->OnReachedDestination.AddDynamic(this, &ACatnip_FollowersCharacter::DestinationReached);
	SkeletalMeshComponent->PlayAnimation(asset, true);
	SAIController->DelayedExecute(0.3f,CommandData);
}

void ACatnip_FollowersCharacter::CommandGather(FCommandData CommandData)
{
	if (!SAIController)
	{
		return;
	}
	IsCommandDone = false;
	SAIController->OnGatheringDone.Clear();
	SAIController->OnGatheringDone.AddDynamic(this, &ACatnip_FollowersCharacter::GatheringDone);
	CommandData.Type = ECommandType::MOVE;
	SAIController->DelayedExecute(0.5f, CommandData);
	CommandData.Type = ECommandType::GATHER;
	SAIController->DelayedExecute(5.0f, CommandData);
}

void ACatnip_FollowersCharacter::CommandDeposit(FCommandData CommandData)
{
	if (!SAIController)
	{
		return;
	}
	IsCommandDone = false;
	SAIController->OnDepositDone.Clear();
	SAIController->OnDepositDone.AddDynamic(this, &ACatnip_FollowersCharacter::DepositDone);
	CommandData.Type = ECommandType::MOVE;
	SAIController->DelayedExecute(2.0f, CommandData);
	CommandData.Type = ECommandType::DEPOSIT;
	SAIController->DelayedExecute(5.0f, CommandData);
}

void ACatnip_FollowersCharacter::CommandConvert(FCommandData CommandData)
{
	if (!SAIController)
	{
		return;
	}
	IsCommandDone = false;
	SAIController->OnDepositDone.Clear();
	SAIController->OnDepositDone.AddDynamic(this, &ACatnip_FollowersCharacter::DepositDone);
	CommandData.Type = ECommandType::MOVE;
	SAIController->DelayedExecute(2.0f, CommandData);
	CommandData.Type = ECommandType::CONVERT;
	SAIController->DelayedExecute(5.0f, CommandData);
}

int32 ACatnip_FollowersCharacter::GetWeight()
{
	int32 wieght = 0;
	for (FItem item : stats.inventory.items) {
		wieght += item.amount;
	}
	return wieght;
}

int32 ACatnip_FollowersCharacter::GetCarryWeight()
{
	return stats.inventory.capacity;
}

int32 ACatnip_FollowersCharacter::GetGatherAmount()
{
	return stats.gatherAmount;
}

FCharacterStats& ACatnip_FollowersCharacter::GetStats()
{
	return stats;
}

void ACatnip_FollowersCharacter::RecieveResources(int32 amount, IResourceInterface* ri)
{
	FItem* itemFound = stats.inventory.FindItem(ri->GetEnumName());

	if (itemFound == NULL) {
		FItem item;
		item.amount = amount;
		item.itemName = ri->GetEnumName();

		stats.inventory.items.Add(item);
	}
	else {
		itemFound->amount += amount;
	}

	inventoryChange.Broadcast(stats.inventory);
}

bool ACatnip_FollowersCharacter::GiveResources(int32 amount, FResourceStats ri)
{

	FString str = UEnums::EnumToString(TEXT("EResourse"), static_cast<uint8>(ri.resourceType));
	FItem* itemFound = stats.inventory.FindItem(str);
	if (itemFound != NULL) {
		itemFound->amount -= amount;
		return true;
	}
	return false;
}

void ACatnip_FollowersCharacter::RecieveResources(FResourceStats ri)
{
	FString str = UEnums::EnumToString(TEXT("EResourse"), static_cast<uint8>(ri.resourceType));
	FItem* itemFound = stats.inventory.FindItem(str);

	if (itemFound == NULL) {
		FItem item;
		item.amount = ri.amount;
		item.itemName = str;

		stats.inventory.items.Add(item);
	}
	else {
		itemFound->amount += ri.amount;
	}

	inventoryChange.Broadcast(stats.inventory);
}

void ACatnip_FollowersCharacter::ClearInventory()
{
	GetStats().inventory.items.Empty();
	inventoryChange.Broadcast(stats.inventory);
}


void ACatnip_FollowersCharacter::DestinationReached(const FCommandData CommandData)
{
	SkeletalMeshComponent->Stop();
	IsCommandDone = true;
	LastCommand.Type = ECommandType::WAIT;
	FVector direction = CommandData.Location - GetActorLocation();
	direction.Normalize();
	TargetOrientation = direction.Rotation();

	ShouldOrientate = true;
	UE_LOG(LogTemp, Warning, TEXT("End a move command"));
}

void ACatnip_FollowersCharacter::GatheringDone(const FCommandData CommandData)
{
	LastCommand.Type = SAIController->CurrentCommandData.Type;
	if (LastCommand.Target != SAIController->CurrentCommandData.Target) 
		LastCommand.Target = SAIController->CurrentCommandData.Target;
	IsCommandDone = true;
	UE_LOG(LogTemp, Warning, TEXT("End a gathering command"));
}

void ACatnip_FollowersCharacter::ConvertDone(const FCommandData CommandData)
{
	IsCommandDone = true;
	LastCommand.Type = ECommandType::WAIT;
	UE_LOG(LogTemp, Warning, TEXT("End a convert command"));
}

void ACatnip_FollowersCharacter::DepositDone(const FCommandData CommandData)
{
	IsCommandDone = true;
	LastCommand.Type = ECommandType::WAIT;
	UE_LOG(LogTemp, Warning, TEXT("End a deposit command"));
}
