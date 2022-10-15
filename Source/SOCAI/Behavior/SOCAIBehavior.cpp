// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior.h"

bool USOCAIBehavior::CalculateCurrentControllerAction_Implementation(const ASOCAIController* InController, FSOCAIAction& OutAction, const FSOCAIAction& InParentAction) const
{
	//Set default values
	OutAction = FSOCAIAction();


	//if we passed in a ParentAction with a specified behavior tag, decide the action on that behavior instead
	if (GetChildBehaviorTags().HasTag(InParentAction.BehaviorTag))
	{
		USOCAIBehavior* ChildBehavior = GetChildBehavior(InParentAction.BehaviorTag);

		if (ChildBehavior)
		{
			const bool bChildSuccess = ChildBehavior->CalculateCurrentControllerAction(InController, OutAction, InParentAction);

			if (bChildSuccess)
			{
				return true;
			}
		}
	}

	//Check each of this node's children and check if we should do that action instead
	for (const FGameplayTag& LocalBehaviorTag : GetChildBehaviorTags())
	{
		USOCAIBehavior* ChildBehavior = GetChildBehavior(LocalBehaviorTag);

		if (!ChildBehavior)
		{
			continue;
		}
		
		const bool bChildSuccess = ChildBehavior->CalculateCurrentControllerAction(InController, OutAction, InParentAction);

		if (bChildSuccess)
		{
			return true;
		}
	}
	
	return false;
}

void USOCAIBehavior::AddChildBehavior(USOCAIBehavior* InChildBehavior)
{
	if (!InChildBehavior)
	{
		return;
	}

	ChildBehaviorMap.Add(InChildBehavior->BehaviorTag, InChildBehavior);
}

USOCAIBehavior* USOCAIBehavior::GetChildBehavior(const FGameplayTag& InBehaviorTag) const
{
	if (GetChildBehaviorTags().IsEmpty())
	{
		return nullptr;
	}

	const TObjectPtr<USOCAIBehavior>* BehaviorPtr = ChildBehaviorMap.Find(InBehaviorTag);

	if (!BehaviorPtr)
	{
		return nullptr;
	}

	return *BehaviorPtr;
}

USOCAIBehavior::USOCAIBehavior(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}
