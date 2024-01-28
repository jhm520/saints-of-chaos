// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior_MoveToEnemyBase.h"

#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"

#pragma region Behavior

bool USOCAIBehavior_MoveToEnemyBase::CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction) const
{
	if (!InActor)
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

	const float CurrentDistance = (CurrentLocation - GetEnemyBaseLocation()).Size();

	if (CurrentDistance < DistanceThreshold)
	{
		return false;
	}
	
	OutAction.BehaviorTag = GetBehaviorTag();
	OutAction.ActionTag = SOCAIActionTags::MoveToLocation;
	OutAction.TargetLocation = GetEnemyBaseLocation();
	
	return Super::CalculateCurrentAction(InActor, OutAction, BehaviorPath, InParentAction);
}
	
#pragma endregion

#pragma region Enemy Base

FVector USOCAIBehavior_MoveToEnemyBase::GetEnemyBaseLocation() const
{
	return FVector::ZeroVector + FVector(100.0f, 0.0f, 0.0f);
}

#pragma endregion
