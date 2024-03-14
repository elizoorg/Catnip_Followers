// Fill out your copyright notice in the Description page of Project Settings.


#include "AGold.h"


AAGold::AAGold()
{
	stats.resourceType = EResourse::Gold;
}

ECommandType AAGold::Use()
{
	return ECommandType::GATHER;
}

