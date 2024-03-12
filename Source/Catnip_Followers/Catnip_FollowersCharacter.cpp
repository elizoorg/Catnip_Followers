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
	SAIController->OnReachedDestination.Clear();
	SAIController->OnReachedDestination.AddDynamic(this, &ACatnip_FollowersCharacter::DestinationReached);
	SAIController->CommandMove(CommandData);
}

void ACatnip_FollowersCharacter::DestinationReached(const FCommandData CommandData)
{
	TargetOrientation = CommandData.Rotation;
	ShouldOrientate = true;
}
