// © 2024 Jade Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "SOCAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API USOCAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()


	/** Should be called once as part of project setup to load global data tables and tags */
	virtual void InitGlobalData() override;
};
