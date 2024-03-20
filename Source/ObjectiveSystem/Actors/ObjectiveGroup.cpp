// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveGroup.h"

#include "Net/UnrealNetwork.h"
#include "ObjectiveSystem/ObjectiveSubsystem.h"
#include "ObjectiveSystem/ObjectiveSystemBlueprintLibrary.h"



void AObjectiveGroup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(AObjectiveGroup, SubObjectives, COND_None, REPNOTIFY_Always);
}
#pragma endregion

void AObjectiveGroup::OnRegistered()
{
	Super::OnRegistered();
	
}

void AObjectiveGroup::OnUnregistered()
{
	Super::OnUnregistered();
}

void AObjectiveGroup::OnRep_SubObjectives()
{
	
}

void AObjectiveGroup::OnSubObjectivesChanged()
{
	K2_OnSubObjectivesChanged();
}

void AObjectiveGroup::OnSubObjectiveSuccess(AObjective* Objective, AActor* Assignee, AActor* InInstigator)
{
	OnSubObjectiveSuccessDelegate.Broadcast(this, Objective, Assignee, InInstigator);
}

void AObjectiveGroup::OnSubObjectiveFailure(AObjective* Objective, AActor* Assignee, AActor* InInstigator)
{
	OnSubObjectiveFailureDelegate.Broadcast(this, Objective, Assignee, InInstigator);
}

void AObjectiveGroup::OnSubObjectiveComplete(AObjective* Objective, AActor* Assignee, AActor* InInstigator)
{
	const bool bObjectiveGroupComplete = IsObjectiveGroupComplete();
	
	if(bObjectiveGroupComplete)
	{
		OnObjectiveComplete.Broadcast(this, Assignee, InInstigator);
	}
}

void AObjectiveGroup::OnSubObjectiveFailed(AObjective* Objective, AActor* Assignee, AActor* InInstigator)
{
	const bool bIsObjectiveGroupFailed = IsObjectiveGroupFailed();


	if (bIsObjectiveGroupFailed)
	{
		OnObjectiveFailed.Broadcast(this, Assignee, InInstigator);
	}
}

bool AObjectiveGroup::IsObjectiveGroupComplete_Implementation() const
{
	//check if all the sub objectives are complete

	//TODO: In the future we can make some of the objectives optional, or make a certain number needed to be completed
	for (AObjective* SubObjective : SubObjectives)
	{
		if (!SubObjective)
		{
			return false;
		}

		if (!SubObjective->IsComplete())
		{
			return false;
		}
	}

	//all sub objectives are complete
	return true;
}
	
bool AObjectiveGroup::IsObjectiveGroupFailed_Implementation() const
{
	//check if any of the sub objectives are failed

	//TODO: In the future we can make some of the objectives optional,
	//or make a certain number needed to be failed in order to fail the group objective
	for (AObjective* SubObjective : SubObjectives)
	{
		if (!SubObjective)
		{
			return false;
		}

		//this objective is failed, so the objective group is failed
		if (SubObjective->IsFailed())
		{
			return true;
		}
	}

	return false;
}

void AObjectiveGroup::AddSubObjective(AObjective* SubObjective)
{
	if (!SubObjective)
	{
		return;
	}
	
	SubObjectives.AddUnique(SubObjective);
	
	SubObjective->OnObjectiveSuccess.AddUniqueDynamic(this, &AObjectiveGroup::OnSubObjectiveSuccess);
	
	SubObjective->OnObjectiveFailure.AddUniqueDynamic(this, &AObjectiveGroup::OnSubObjectiveFailure);
	
	SubObjective->OnObjectiveComplete.AddUniqueDynamic(this, &AObjectiveGroup::OnSubObjectiveComplete);
	
	SubObjective->OnObjectiveFailed.AddUniqueDynamic(this, &AObjectiveGroup::OnSubObjectiveFailed);
}

void AObjectiveGroup::RemoveSubObjective(AObjective* SubObjective)
{
	if (!SubObjective)
	{
		return;
	}

	SubObjectives.Remove(SubObjective);
}