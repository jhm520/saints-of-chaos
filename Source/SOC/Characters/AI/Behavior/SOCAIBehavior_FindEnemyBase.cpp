// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior_FindEnemyBase.h"

#include "SOC/Gameplay/Buildings/Building.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "EngineUtils.h"
#include "SOC/Gameplay/Buildings/BuildingSubsystem.h"

#pragma region Framework
USOCAIBehavior_FindEnemyBase::USOCAIBehavior_FindEnemyBase()
{
	DistanceThreshold = 100.0f;
}
#pragma endregion

#pragma region Behavior

bool USOCAIBehavior_FindEnemyBase::CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction) const
{
	if (!InActor)
	{
		return false;
	}
	
	AActor* EnemyBase = GetEnemyBase(InActor);
	
	if (!EnemyBase)
	{
		return false;
	}
	
	OutAction.BehaviorTag = GetBehaviorTag();
	OutAction.TargetActor = EnemyBase;
	
	return Super::CalculateCurrentAction(InActor, OutAction, BehaviorPath, OutAction);
}
	
#pragma endregion

#pragma region Enemy Base

bool USOCAIBehavior_FindEnemyBase::GetEnemyBaseLocation(const AActor* InActor, FVector& OutEnemyBaseLocation) const
{
	AActor* EnemyBase = GetEnemyBase(InActor);

	if (!EnemyBase)
	{
		return false;
	}

	OutEnemyBaseLocation = EnemyBase->GetActorLocation();
	return true;
}

AActor* USOCAIBehavior_FindEnemyBase::GetEnemyBase(const AActor* InActor) const
{
	if (!InActor)
	{
		return nullptr;
	}

	AActor* Director = GetDirector(InActor);

	if (!Director)
	{
		return nullptr;
	}

	UBuildingSubsystem* BuildingSubsystem = UBuildingSubsystem::Get(Director);

	if (!BuildingSubsystem)
	{
		return nullptr;
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

		return Building;
	}

	return nullptr;
}

#pragma endregion