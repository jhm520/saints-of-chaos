// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior_MoveToEnemyBase.h"

#pragma region Behavior

bool USOCAIBehavior_MoveToEnemyBase::CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction) const
{
	OutAction.BehaviorTag = GetBehaviorTag();
	OutAction.ActionTag = SOCAIActionTags::MoveToLocation;
	OutAction.TargetLocation = GetEnemyBaseLocation();
	
	return Super::CalculateCurrentAction(InActor, OutAction, BehaviorPath, InParentAction);
}
	
#pragma endregion

#pragma region Enemy Base

FVector USOCAIBehavior_MoveToEnemyBase::GetEnemyBaseLocation() const
{
	return FVector::ZeroVector;
}

#pragma endregion
