// © 2024 Jade Miller. All rights reserved

#include "SOCAssetManager.h"

#include "AbilitySystemGlobals.h"

void USOCAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}
