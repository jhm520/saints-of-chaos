// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior.h"

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
