// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior.h"

bool USOCAIBehavior::CalculateCurrentAction_Implementation(const AActor* InActor, FSOCAIAction& OutAction, FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction) const
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, GetBehaviorTag().ToString());

	//add the tag to the behavior path, letting the other nodes know that we've traversed this node
	BehaviorPath.AddTag(GetBehaviorTag());
	
	//if we passed in a ParentAction with a specified behavior tag, decide the action on that behavior instead
	if (GetChildBehaviorTags().HasTag(InParentAction.BehaviorTag))
	{
		USOCAIBehavior* ChildBehavior = GetChildBehavior(InParentAction.BehaviorTag);

		if (ChildBehavior)
		{
			const bool bChildSuccess = ChildBehavior->CalculateCurrentAction(InActor, OutAction,BehaviorPath, InParentAction);

			if (bChildSuccess)
			{
				return true;
			}
		}
	}
	
	//Check each of this node's children and check if we should do that action instead
	for (const FGameplayTag& LocalBehaviorTag : GetChildBehaviorTags())
	{
		//Do not traverse nodes that we've already traversed on this path to avoid infinite looping
		if (BehaviorPath.HasTag(LocalBehaviorTag))
		{
			continue;
		}
		
		USOCAIBehavior* ChildBehavior = GetChildBehavior(LocalBehaviorTag);

		if (!ChildBehavior)
		{
			continue;
		}
		
		const bool bChildSuccess = ChildBehavior->CalculateCurrentAction(InActor, OutAction,BehaviorPath, InParentAction);

		if (bChildSuccess)
		{
			return true;
		}
	}

	//If its already decided that we're executing an action, return true
	if (InParentAction.ActionTag != SOCAIActionTags::None)
	{
		return true;
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
