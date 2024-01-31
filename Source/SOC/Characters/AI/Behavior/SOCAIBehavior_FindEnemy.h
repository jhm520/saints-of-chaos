// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOCAI/Behavior/SOCAIBehavior.h"
#include "SOCAIBehavior_FindEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API USOCAIBehavior_FindEnemy : public USOCAIBehavior
{
	GENERATED_BODY()

#pragma region Behavior

public:
	virtual bool CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction = FSOCAIAction()) const override;
	
#pragma endregion
	
};
