// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior.h"

bool USOCAIBehavior::CalculateCurrentControllerAction_Implementation(const ASOCAIController* InController, FSOCAIAction& OutAction) const
{
	OutAction.ActionTag = SOCAIActionTags::Idle;
	OutAction.TargetLocation = FVector::ZeroVector;
	OutAction.TargetActor = nullptr;
	
	return true;
}

void USOCAIBehavior::AddChildBehavior(USOCAIBehavior* InChildBehavior)
{
	if (!InChildBehavior)
	{
		return;
	}

	ChildBehaviorSet.Add(InChildBehavior);
}

USOCAIBehavior::USOCAIBehavior(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	for (const FGameplayTag& Tag : ChildBehaviorTags)
	{
		
	}
}
