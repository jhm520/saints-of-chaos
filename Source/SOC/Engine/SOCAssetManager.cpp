// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAssetManager.h"

#include "AbilitySystemGlobals.h"

void USOCAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}
