// © 2024 John Henry Miller. All rights reserved

#include "SOCAIBehavior_MoveToCombatRange.h"

#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"

USOCAIBehavior_MoveToCombatRange::USOCAIBehavior_MoveToCombatRange()
{
	DistanceThreshold = 150.0f;
}

bool USOCAIBehavior_MoveToCombatRange::CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction) const
{
	AActor* TargetActor = InParentAction.TargetActor;

	if (!TargetActor)
	{
		return false;
	}

	const ISOCAIBehaviorInterface* BehaviorInterface = Cast<ISOCAIBehaviorInterface>(InActor);

	if (!BehaviorInterface)
	{
		return false;
	}

	const AActor* AvatarActor = BehaviorInterface->GetAvatarActor();

	if (!AvatarActor)
	{
		return false;
	}

	const FVector& CurrentLocation = AvatarActor->GetActorLocation();

	const FVector TargetLocation = TargetActor->GetActorLocation();
	
	const float CurrentDistance = (CurrentLocation - TargetLocation).Size();

	// If we are already within the distance threshold, we don't need to move
	if (CurrentDistance < DistanceThreshold)
	{
		return false;
	}

	OutAction.BehaviorTag = SOCAIBehaviorTags::MoveToCombatRange;
	OutAction.ActionTag = SOCAIActionTags::MoveToActor;
	OutAction.TargetActor = TargetActor;
	
	return Super::CalculateCurrentAction(InActor, OutAction, BehaviorPath, InParentAction);
}