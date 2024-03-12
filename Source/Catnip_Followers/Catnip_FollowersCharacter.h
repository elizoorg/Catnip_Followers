// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Selectable.h"
#include "GameFramework/Character.h"
#include "Catnip_FollowersCharacter.generated.h"

class AAI_Unit_Controller;

UCLASS(Blueprintable)
class ACatnip_FollowersCharacter : public ACharacter, public ISelectable
{
	GENERATED_BODY()

public:
	ACatnip_FollowersCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual  void Select() override;
	virtual  void DeSelect() override;
	virtual  void HighLight(const bool Highlight) override;

	UPROPERTY()
	bool Selected;


	UFUNCTION()
	void SetAIController(AAI_Unit_Controller* NewAIController) { SAIController = NewAIController; };

	UPROPERTY()
	AAI_Unit_Controller* SAIController;


	UPROPERTY()
	bool ShouldOrientate;

	UPROPERTY()
	FRotator TargetOrientation;

	UFUNCTION()
	void SetOrientation(const float DeltaTime);

	UFUNCTION()
	bool IsOrientated() const;


	UFUNCTION()
	void CommandMove(const FCommandData CommandData);

	UFUNCTION()
	void DestinationReached(const FCommandData CommandData);

private:
	

};

