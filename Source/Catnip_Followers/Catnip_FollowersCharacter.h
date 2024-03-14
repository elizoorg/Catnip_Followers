// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIData.h"
#include "ResourceInterface.h"
#include "Selectable.h"
#include "GameFramework/Character.h"
#include "StorageInterface.h"
#include "Catnip_FollowersCharacter.generated.h"

class AAI_Unit_Controller;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryChange, FInventory, newInventory);

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

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	UAnimationAsset* asset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY()
	FCommandData LastCommand;

	UPROPERTY()
	bool IsCommandDone;

	UFUNCTION()
	void SetOrientation(const float DeltaTime);

	UFUNCTION()
	bool IsOrientated() const;


	UFUNCTION()
	void CommandMove(const FCommandData CommandData);

	UFUNCTION()
	void CommandGather(FCommandData CommandData);

	UFUNCTION()
	void CommandDeposit(FCommandData CommandData);

	UFUNCTION()
	void CommandConvert(FCommandData CommandData);

	FInventoryChange inventoryChange;

	UFUNCTION()
	virtual int32 GetWeight();
	UFUNCTION()
	virtual int32 GetCarryWeight();
	UFUNCTION()
	virtual int32 GetGatherAmount();
	UFUNCTION()
	virtual FCharacterStats& GetStats();

	virtual void RecieveResources(int32 amount, IResourceInterface* ri);

	virtual bool GiveResources(int32 amount, FResourceStats ri);

	virtual void RecieveResources(FResourceStats ri);

	void ClearInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FCharacterStats stats;

	UFUNCTION()
	void DestinationReached(const FCommandData CommandData);

	UFUNCTION()
	void GatheringDone(const FCommandData CommandData);

	UFUNCTION()
	void ConvertDone(const FCommandData CommandData);


	UFUNCTION()
	void DepositDone(const FCommandData CommandData);

private:
	

};

