// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Catnip_FollowersCharacter.generated.h"

UCLASS(Blueprintable)
class ACatnip_FollowersCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACatnip_FollowersCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

private:

};

