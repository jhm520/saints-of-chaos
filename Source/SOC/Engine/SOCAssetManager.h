// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "SOCAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API USOCAssetManager : public UAssetManager
{
	GENERATED_BODY()

	virtual void StartInitialLoading() override;
	
};
