// Copyright Epic Games, Inc. All Rights Reserved.

#include "Catnip_FollowersCharacter.h"

#include "AI_Unit_Controller.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Materials/Material.h"
#include "Engine/World.h"

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
}
