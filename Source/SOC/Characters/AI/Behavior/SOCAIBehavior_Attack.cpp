// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior_Attack.h"

#pragma region Behavior

bool USOCAIBehavior_Attack::CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction) const
{
	//if the parent did not decide on a target actor, we cannot attack
	if (!InParentAction.TargetActor)
	{
		return false;
	}
	
	OutAction.BehaviorTag = SOCAIBehaviorTags::Attack;
	OutAction.ActionTag = SOCAIActionTags::Attack;
	OutAction.TargetActor = InParentAction.TargetActor;
	
	return Super::CalculateCurrentAction(InActor, OutAction, BehaviorPath, InParentAction);
}

#pragma endregion