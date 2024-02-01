// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior_MoveToCombatRange.h"

bool USOCAIBehavior_MoveToCombatRange::CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction) const
{
	AActor* TargetActor = InParentAction.TargetActor;

	if (!TargetActor)
	{
		return false;
	}

	OutAction.BehaviorTag = SOCAIBehaviorTags::MoveToCombatRange;
	OutAction.ActionTag = SOCAIActionTags::MoveToActor;
	OutAction.TargetActor = TargetActor;
	
	return Super::CalculateCurrentAction(InActor, OutAction, BehaviorPath, InParentAction);
}
