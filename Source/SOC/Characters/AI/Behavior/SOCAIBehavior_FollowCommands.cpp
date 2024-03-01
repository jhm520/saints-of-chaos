// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior_FollowCommands.h"

#include "SOC/Gameplay/Buildings/Building.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "EngineUtils.h"
#include "CommandSystem/CommandInfo.h"
#include "CommandSystem/CommandSystemBlueprintLibrary.h"
#include "CommandSystem/Interfaces/CommandableInterface.h"
#include "SOC/Gameplay/Buildings/BuildingSubsystem.h"

#pragma region Framework
USOCAIBehavior_FollowCommands::USOCAIBehavior_FollowCommands()
{
}
#pragma endregion

#pragma region Behavior
UE_DISABLE_OPTIMIZATION
bool USOCAIBehavior_FollowCommands::CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction) const
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

	FCommandInstance CurrentCommand;

	UCommandSystemBlueprintLibrary::GetCurrentCommand(AvatarActor, CurrentCommand);

	if (CurrentCommand.IsValid())
	{
		OutAction.BehaviorTag = GetBehaviorTag();
		
		return true;
	}
	
	return Super::CalculateCurrentAction(InActor, OutAction, BehaviorPath, InParentAction);
}
UE_ENABLE_OPTIMIZATION
#pragma endregion

#pragma region Enemy Base

bool USOCAIBehavior_FollowCommands::GetEnemyBaseLocation(const AActor* InActor, FVector& OutEnemyBaseLocation) const
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