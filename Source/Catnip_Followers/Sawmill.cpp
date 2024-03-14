// Fill out your copyright notice in the Description page of Project Settings.


#include "Sawmill.h"


// Sets default values
ASawmill::ASawmill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
}

// Called when the game starts or when spawned
void ASawmill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASawmill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASawmill::Select()
{
	Selected = true;
	HighLight(Selected);
}

void ASawmill::DeSelect()
{
	Selected = false;
	HighLight(Selected);
}

void ASawmill::HighLight(const bool Highlight)
{
	UE_LOG(LogTemp, Warning, TEXT("Hello World bui"));

	TArray<UPrimitiveComponent*> Components;
	GetComponents<UPrimitiveComponent>(Components);
	for (UPrimitiveComponent* VisualComp : Components)
	{
		if (UPrimitiveComponent* Prim = Cast <UPrimitiveComponent>(VisualComp))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hello World xdd"));

			Prim->SetRenderCustomDepth(Highlight);
		}
	}
}

ECommandType ASawmill::Use()
{
	return ECommandType::CONVERT;
}

FResourceStats ASawmill::FromConvert()
{
	return fromConvert;
}

FResourceStats ASawmill::ToConvert()
{
	return toConvert;
}
