// Fill out your copyright notice in the Description page of Project Settings.

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
