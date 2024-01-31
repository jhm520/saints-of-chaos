// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior_MoveToEnemyBase.h"

#include "SOC/Gameplay/Buildings/Building.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "EngineUtils.h"
#include "SOC/Gameplay/Buildings/BuildingSubsystem.h"

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

	FVector EnemyBaseLocation;

	const bool bFoundEnemyBase = GetEnemyBaseLocation(InActor, EnemyBaseLocation);

	if (!bFoundEnemyBase)
	{
		return false;
	}

	const float CurrentDistance = (CurrentLocation - EnemyBaseLocation).Size();

	if (CurrentDistance < DistanceThreshold)
	{
		return false;
	}
	
	OutAction.BehaviorTag = GetBehaviorTag();
	OutAction.ActionTag = SOCAIActionTags::MoveToLocation;
	OutAction.TargetLocation = EnemyBaseLocation;
	
	return Super::CalculateCurrentAction(InActor, OutAction, BehaviorPath, InParentAction);
}
	
#pragma endregion

#pragma region Enemy Base

bool USOCAIBehavior_MoveToEnemyBase::GetEnemyBaseLocation(const AActor* InActor, FVector& OutEnemyBaseLocation) const
{
	if (!InActor)
	{
		return false;
	}

	AActor* Director = GetDirector(InActor);

	if (!Director)
	{
		return false;
	}

	UBuildingSubsystem* BuildingSubsystem = UBuildingSubsystem::Get(Director);

	if (!BuildingSubsystem)
	{
		return false;
	}

	TArray<ASOCBuilding*> Buildings = BuildingSubsystem->GetAllBuildings();

	for (ASOCBuilding* Building : Buildings)
	{
		if (!Building)
		{
			continue;
		}

		if (!Director->Implements<UAttitudeInterface>())
		{
			continue;
		}
		
		const EAttitude Attitude = IAttitudeInterface::Execute_GetAttitudeTowards(Director, Building);

		if (Attitude < EAttitude::Hostile)
		{
			continue;
		}
		
		OutEnemyBaseLocation = Building->GetActorLocation();
		return true;
	}
	
	return false;
}

#pragma endregion