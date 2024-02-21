// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior_Attack.h"

#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"

#pragma region Behavior

USOCAIBehavior_Attack::USOCAIBehavior_Attack()
{
	DistanceThreshold = 150.0f;
}

bool USOCAIBehavior_Attack::CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction) const
{
	//if the parent did not decide on a target actor, we cannot attack
	if (!InParentAction.TargetActor)
	{
		return false;
	}

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

	// If we are outside the distance threshold, we can't attack
	//TODO: We should make this logic generic and move it to the base class
	if (CurrentDistance > DistanceThreshold)
	{
		return false;
	}
	
	OutAction.BehaviorTag = SOCAIBehaviorTags::Attack;
	OutAction.ActionTag = SOCAIActionTags::Attack;
	OutAction.TargetActor = InParentAction.TargetActor;
	
	return Super::CalculateCurrentAction(InActor, OutAction, BehaviorPath, InParentAction);
}

#pragma endregion