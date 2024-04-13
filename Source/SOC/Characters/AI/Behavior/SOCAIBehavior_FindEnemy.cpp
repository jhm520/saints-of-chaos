// © 2024 John Henry Miller. All rights reserved

#include "SOCAIBehavior_FindEnemy.h"

#include "AggroSystem/Components/AggroSystemComponent.h"
#include "AggroSystem/Interfaces/AggroInterface.h"

bool USOCAIBehavior_FindEnemy::CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction) const
{
	const IAggroInterface* AggroInterface = Cast<IAggroInterface>(InActor);

	if (!AggroInterface)
	{
		return false;
	}
	
	UAggroSystemComponent* AggroSystemComponent = AggroInterface->GetAggroSystemComponent();

	if (!AggroSystemComponent)
	{
		return false;
	}

	AActor* ClosestEnemy = AggroSystemComponent->FindAggroTarget();

	if (!ClosestEnemy)
	{
		return false;
	}

	OutAction.BehaviorTag = SOCAIBehaviorTags::FindEnemy;
	OutAction.TargetActor = ClosestEnemy;
	
	return Super::CalculateCurrentAction(InActor, OutAction, BehaviorPath, OutAction);
}