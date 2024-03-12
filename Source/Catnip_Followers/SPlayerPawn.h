// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIData.h"
#include "GameFramework/Pawn.h"
#include "SPlayerPawn.generated.h"


class UCameraComponent;
class USpringArmComponent;



UCLASS()
class CATNIP_FOLLOWERS_API ASPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Forward(float AxisValue);

	UFUNCTION()
	void Right(float AxisValue);

	UFUNCTION()
	void Zoom(float AxisValue);

	UFUNCTION()
	void RotateRight();

	UFUNCTION()
	void RotateLeft();

	UFUNCTION()
	void EnableRotate();

	UFUNCTION()
	void DisableRotate();

	UFUNCTION()
	void RotateHorizontal(float AxisValue);

	UFUNCTION()
	void RotateVertical(float AxisValue);



	UFUNCTION()
	void MouseLeftPressed();

	UFUNCTION()
	void MouseRightPressed();

	UFUNCTION()
	void MouseLeftReleased();

	UFUNCTION()
	void MouseRightReleased();

	UFUNCTION()
	AActor* GetSelectedObject();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Camera");
	float MoveSpeed = 20.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Camera");
	float RotateSpeed = 2.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Camera");
	float RotatePitchMin = 10.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Camera");
	float RotatePitchMax = 80.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Camera");
	float ZoomSpeed = 2.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Camera");
	float MinZoom = 500.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Camera");
	float MaxZoom = 4000.0f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UFUNCTION()
	void CameraBounds();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = ( AllowPrivateAccess = "true" ));
	USceneComponent* SceneComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"));
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"));
	UCameraComponent* CameraComponent;

	UPROPERTY()
	FVector TargetLocation;

	UPROPERTY()
	FRotator TargetRotation;

	UPROPERTY()
	float TargetZoom;

	UPROPERTY()
	bool CanRotate;


	UFUNCTION()
	FCommandData CreateCommandData(const ECommandType Type) const;

	UFUNCTION()
	void Command();

	UPROPERTY()
	FVector CommandLocation;



};
