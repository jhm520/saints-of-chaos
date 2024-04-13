// © 2024 John Henry Miller. All rights reserved

#include "SOCAIBehavior_MoveToEnemyBase.h"

#include "SOC/Gameplay/Buildings/Building.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "EngineUtils.h"
#include "SOC/Gameplay/Buildings/BuildingSubsystem.h"

#pragma region Framework
USOCAIBehavior_MoveToEnemyBase::USOCAIBehavior_MoveToEnemyBase()
{
	DistanceThreshold = 100.0f;
}
#pragma endregion

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

	if (!IsValid(AvatarActor))
	{
		return false;
	}

	const FVector& CurrentLocation = AvatarActor->GetActorLocation();

	AActor* EnemyBase = InParentAction.TargetActor;
	
	if (!EnemyBase)
	{
		return false;
	}

	const FVector& EnemyBaseLocation = InParentAction.TargetActor->GetActorLocation();

	const float CurrentDistance = (CurrentLocation - EnemyBaseLocation).Size();

	// If we are already within the distance threshold, we don't need to move
	if (CurrentDistance < DistanceThreshold)
	{
		return false;
	}
	
	OutAction.BehaviorTag = GetBehaviorTag();
	OutAction.ActionTag = SOCAIActionTags::MoveToActor;
	OutAction.TargetActor = EnemyBase;
	
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