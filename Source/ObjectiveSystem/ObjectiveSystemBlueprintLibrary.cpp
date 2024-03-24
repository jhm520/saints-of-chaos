// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveSystemBlueprintLibrary.h"

#include "ObjectiveSubsystem.h"
#include "Actors/Objective.h"
#include "Actors/ObjectiveGroup.h"
#include "Components/ObjectiveAssigneeComponent.h"
#include "Components/ObjectiveTrackerComponent.h"
#include "Interfaces/ObjectiveAssigneeInterface.h"
#include "Interfaces/ObjectiveTrackerInterface.h"

void UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByCollection(AActor* ObjectiveTracker, UObjectiveInfoCollection* ObjectiveCollection, TArray<AActor*> Assignees, TArray<AObjective*>& OutObjectives)
{
	if (!ObjectiveTracker || !ObjectiveCollection)
	{
		return;
	}

	IObjectiveTrackerInterface* ObjectiveTrackerInterface = Cast<IObjectiveTrackerInterface>(ObjectiveTracker);

	if (!ObjectiveTrackerInterface)
	{
		return;
	}

	UObjectiveTrackerComponent* ObjectiveTrackerComponent = ObjectiveTrackerInterface->GetObjectiveTrackerComponent();

	if (!ObjectiveTrackerComponent)
	{
		return;
	}

	ObjectiveTrackerComponent->SetupObjectivesByCollection(ObjectiveCollection, Assignees, OutObjectives);
}

void UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByTags(AActor* ObjectiveTracker, FGameplayTagContainer ObjectiveTags, TArray<AActor*> Assignees, TArray<AObjective*>& OutObjectives)
{
	if (!ObjectiveTracker)
	{
		return;
	}

	IObjectiveTrackerInterface* ObjectiveTrackerInterface = Cast<IObjectiveTrackerInterface>(ObjectiveTracker);

	if (!ObjectiveTrackerInterface)
	{
		return;
	}

	UObjectiveTrackerComponent* ObjectiveTrackerComponent = ObjectiveTrackerInterface->GetObjectiveTrackerComponent();

	if (!ObjectiveTrackerComponent)
	{
		return;
	}

	ObjectiveTrackerComponent->SetupObjectivesByTags(ObjectiveTags, Assignees, OutObjectives);
}

void UObjectiveSystemBlueprintLibrary::BeginObjectivesForActorByCollection(AActor* ObjectiveTracker, UObjectiveInfoCollection* ObjectiveCollection, const FGameplayTagContainer& OptionalTags)
{
	if (!ObjectiveTracker || !ObjectiveCollection)
	{
		return;
	}

	IObjectiveTrackerInterface* ObjectiveTrackerInterface = Cast<IObjectiveTrackerInterface>(ObjectiveTracker);

	if (!ObjectiveTrackerInterface)
	{
		return;
	}

	UObjectiveTrackerComponent* ObjectiveTrackerComponent = ObjectiveTrackerInterface->GetObjectiveTrackerComponent();

	if (!ObjectiveTrackerComponent)
	{
		return;
	}

	ObjectiveTrackerComponent->BeginObjectivesByCollection(ObjectiveCollection);
}

void UObjectiveSystemBlueprintLibrary::ProgressObjectivesForAssigneeByTags(AActor* Assignee, const FGameplayTagContainer& ObjectiveTags, bool bSuccess)
{
	if (!Assignee)
	{
		return;
	}

	IObjectiveAssigneeInterface* AssigneeInterface = Cast<IObjectiveAssigneeInterface>(Assignee);

	if (!AssigneeInterface)
	{
		return;
	}
	
	AActor* LocalAssignee = AssigneeInterface->GetAssignee();

	UObjectiveAssigneeComponent* AssigneeComponent = AssigneeInterface->GetObjectiveAssigneeComponent();

	if (!AssigneeComponent)
	{
		return;
	}

	AssigneeComponent->ProgressObjectivesForAssigneeByTags(LocalAssignee, ObjectiveTags, bSuccess);
}

void UObjectiveSystemBlueprintLibrary::GetObjectivesByTags(UObject* WorldContextObject, const FGameplayTagContainer ObjectiveTags, TArray<AObjective*>& OutObjectives)
{
	UObjectiveSubsystem* ObjectiveSubsystem = UObjectiveSubsystem::Get(WorldContextObject->GetWorld());

	if (!ObjectiveSubsystem)
	{
		return;
	}

	ObjectiveSubsystem->GetObjectivesByTags(ObjectiveTags, OutObjectives);
}

bool UObjectiveSystemBlueprintLibrary::GetAssignedObjectives(UObject* WorldContextObject, AActor* Assignee, TArray<AObjective*>& OutObjectives, FGameplayTagContainer ObjectiveTags)
{
	if (!WorldContextObject || !Assignee)
	{
		return false;
	}
	TArray<AObjective*> Objectives;
	UObjectiveSystemBlueprintLibrary::GetObjectivesByTags(WorldContextObject, ObjectiveTags, Objectives);

	for (AObjective* Objective : Objectives)
	{
		if (!Objective)
		{
			continue;
		}

		if (!ObjectiveTags.IsEmpty() && !Objective->GetObjectiveTags().HasAny(ObjectiveTags))
		{
			continue;
		}

		if (!Objective->IsAssigned(Assignee))
		{
			continue;
		}

		OutObjectives.Add(Objective);
	}

	return OutObjectives.Num() > 0;
}

bool UObjectiveSystemBlueprintLibrary::GetObjectiveAssigneesByTags(UObject* WorldContextObject, TArray<AActor*>& OutAssignees, FGameplayTagContainer ObjectiveTags)
{
	if (!WorldContextObject)
	{
		return false;
	}
	TArray<AObjective*> Objectives;
	UObjectiveSystemBlueprintLibrary::GetObjectivesByTags(WorldContextObject, ObjectiveTags, Objectives);

	for (AObjective* Objective : Objectives)
	{
		if (!Objective)
		{
			continue;
		}

		TArray<AActor*> Assignees = Objective->GetAssignees();

		for (AActor* Assignee : Assignees)
		{
			if (!Assignee)
			{
				continue;
			}

			OutAssignees.AddUnique(Assignee);
		}
	}

	return OutAssignees.Num() > 0;
}

//returns true if all assignees have completed the objectives with the specified tags
bool UObjectiveSystemBlueprintLibrary::HaveAllAssigneesCompletedObjectivesByTags(UObject* WorldContextObject, TArray<AActor*>& OutAssignees, FGameplayTagContainer ObjectiveTags)
{
	if (!WorldContextObject)
	{
		return false;
	}

	TArray<AObjective*> Objectives;
	GetObjectivesByTags(WorldContextObject, ObjectiveTags, Objectives);

	TArray<AActor*> LocalAssignees;
	
	for (AObjective* Objective : Objectives)
	{
		if (!Objective)
		{
			continue;
		}

		TArray<AActor*> Assignees = Objective->GetAssignees();

		for (AActor* Assignee : Assignees)
		{
			if (!Assignee)
			{
				continue;
			}

			if (!Objective->HasAssigneeCompleted(Assignee))
			{
				return false;
			}
			
			LocalAssignees.AddUnique(Assignee);
		}
	}

	OutAssignees = LocalAssignees;

	return OutAssignees.Num() > 0;
}

//assigns the input objectives to the specified ObjectiveGroup
void UObjectiveSystemBlueprintLibrary::AddObjectivesToObjectiveGroup(UObject* WorldContextObject, const TArray<AObjective*> Objectives, AObjectiveGroup* ObjectiveGroup)
{
	if (!WorldContextObject)
	{
		return;
	}
	
	if (!ObjectiveGroup)
	{
		return;
	}
	
	for (AObjective* Objective : Objectives)
	{
		if (!Objective)
		{
			continue;
		}

		ObjectiveGroup->AddSubObjective(Objective);
	}
}
	