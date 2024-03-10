// Copyright [2022] Psychedelic Games. All rights reserved!


#include "ObjectiveTrackerComponent.h"

#include "ObjectiveSystem/Actors/Objective.h"
#include "GameFramework/GameStateBase.h"
#include "ObjectiveSystem/DataAssets/ObjectiveInfoCollection.h"
#include "ObjectiveSystem/Interfaces/ObjectiveTrackerInterface.h"

#pragma region Framework
// Sets default values for this component's properties
UObjectiveTrackerComponent::UObjectiveTrackerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UObjectiveTrackerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UObjectiveTrackerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#pragma endregion

#pragma region Objective System

void UObjectiveTrackerComponent::SetupObjectives()
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	
	if (!IsValid(ObjectiveInfoCollection))
	{
		return;
	}

	TArray<FObjectiveInfo> ObjectiveInfos = ObjectiveInfoCollection->GetObjectiveInfos();

	for (const FObjectiveInfo& ObjectiveInfo : ObjectiveInfos)
	{
		SetupObjective(ObjectiveInfo);
	}
}

void UObjectiveTrackerComponent::SetupObjective(const FObjectiveInfo& ObjectiveInfo)
{
	IObjectiveTrackerInterface* ObjectiveTrackerInterface = Cast<IObjectiveTrackerInterface>(GetOwner());

	if (!ObjectiveTrackerInterface)
	{
		return;
	}
		
	AObjective* NewObjective = CreateObjective(ObjectiveInfo);

	if (!NewObjective)
	{
		return;
	}

	TArray<AActor*> Assignees = ObjectiveTrackerInterface->GetAssignees(NewObjective);

	for (AActor* Assignee : Assignees)
	{
		if (!Assignee)
		{
			continue;
		}
		
		AssignObjective(NewObjective, Assignee);
	}
}

void UObjectiveTrackerComponent::BeginObjectives()
{
	for (AObjective* Objective : Objectives)
	{
		if (!Objective)
		{
			continue;
		}

		Objective->Begin();
	}
}

void UObjectiveTrackerComponent::ProgressObjective(AActor* Assignee, AActor* Instigator, const FGameplayTag& ObjectiveTag, bool bSuccess)
{
	for (AObjective* Objective : Objectives)
	{
		if (!Objective)
		{
			return;
		}

		if (!Objective->ObjectiveTags.HasTag(ObjectiveTag))
		{
			continue;
		}

		if (bSuccess)
		{
			Objective->Success(Assignee, Instigator);
		}
		else
		{
			Objective->Failure(Assignee, Instigator);
		}
	}
}

void UObjectiveTrackerComponent::OnObjectiveComplete()
{
	
}

AObjective* UObjectiveTrackerComponent::CreateObjective(const FObjectiveInfo& ObjectiveInfo)
{
	if (!GetOwner()->GetWorld())
	{
		return nullptr;
	}
		
	AObjective* NewObjective = GetWorld()->SpawnActorDeferred<AObjective>(ObjectiveInfo.ObjectiveClass, FTransform::Identity, GetOwner(), nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	if (!NewObjective)
	{
		return nullptr;
	}
	
	NewObjective->FinishSpawning(FTransform::Identity);

	Objectives.Add(NewObjective);

	return NewObjective;
}

void UObjectiveTrackerComponent::AssignObjective(AObjective* Objective, AActor* Assignee)
{
	if (!Objective || !Assignee)
	{
		return;
	}

	Objective->Assign(Assignee);
}

#pragma endregion


