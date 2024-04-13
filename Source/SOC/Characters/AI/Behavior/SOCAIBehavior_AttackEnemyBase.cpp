// © 2024 John Henry Miller. All rights reserved

#include "SOCAIBehavior_AttackEnemyBase.h"

#include "SOC/Gameplay/Buildings/Building.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "EngineUtils.h"
#include "SOC/Gameplay/Buildings/BuildingSubsystem.h"

#pragma region Framework
USOCAIBehavior_AttackEnemyBase::USOCAIBehavior_AttackEnemyBase()
{
	DistanceThreshold = 100.0f;
}
#pragma endregion

#pragma region Behavior

bool USOCAIBehavior_AttackEnemyBase::CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction) const
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
	
	OutAction.BehaviorTag = GetBehaviorTag();
	OutAction.ActionTag = SOCAIActionTags::Attack;
	OutAction.TargetActor = EnemyBase;
	
	return Super::CalculateCurrentAction(InActor, OutAction, BehaviorPath, InParentAction);
}
	
#pragma endregion

#pragma region Enemy Base

bool USOCAIBehavior_AttackEnemyBase::GetEnemyBaseLocation(const AActor* InActor, FVector& OutEnemyBaseLocation) const
{
	AActor* EnemyBase = GetEnemyBase(InActor);

	if (!EnemyBase)
	{
		return false;
	}

	OutEnemyBaseLocation = EnemyBase->GetActorLocation();
	return true;
}

AActor* USOCAIBehavior_AttackEnemyBase::GetEnemyBase(const AActor* InActor) const
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