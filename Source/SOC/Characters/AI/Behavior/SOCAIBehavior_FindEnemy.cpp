// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior_FindEnemy.h"

bool USOCAIBehavior_FindEnemy::CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction) const
{
	return Super::CalculateCurrentAction(InActor, OutAction, BehaviorPath, InParentAction);
}
