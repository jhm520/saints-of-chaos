// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior.h"

bool USOCAIBehavior::CalculateCurrentControllerAction_Implementation(const ASOCAIController* InController, FSOCAIAction& OutAction, const FSOCAIAction& InParentAction) const
{
	//Set default values
	OutAction = FSOCAIAction();
	
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
	
}
