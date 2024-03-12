// Fill out your copyright notice in the Description page of Project Settings.


#include "Stock.h"

AStock::AStock() : Super()
{
	inventory.capacity = 1000;
}

void AStock::Select()
{
	Selected = true;
	HighLight(Selected);
}

void AStock::DeSelect()
{
	Selected = false;
	HighLight(Selected);
}

void AStock::HighLight(const bool Highlight)
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
