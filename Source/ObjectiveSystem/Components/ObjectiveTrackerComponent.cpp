//


#include "ObjectiveTrackerComponent.h"

#include "ObjectiveSystem/Actors/Objective.h"
#include "GameFramework/GameStateBase.h"
#include "ObjectiveSystem/ObjectiveSubsystem.h"
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
	// ...
	UObjectiveSubsystem* ObjectiveSubsystem = UObjectiveSubsystem::Get(this);

	if (ObjectiveSubsystem)
	{
		ObjectiveSubsystem->RegisterObjectiveTrackerComponent(this);
	}
}

void UObjectiveTrackerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// ...
	// ...
	UObjectiveSubsystem* ObjectiveSubsystem = UObjectiveSubsystem::Get(this);

	if (ObjectiveSubsystem)
	{
		ObjectiveSubsystem->UnregisterObjectiveTrackerComponent(this);
	}
	
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void UObjectiveTrackerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#pragma endregion

#pragma region Objective System

//sets up all the objectives available on this tracker
void UObjectiveTrackerComponent::SetupAllObjectives(TArray<AActor*> Assignees, TArray<AObjective*>& OutObjectives)
{
	for (UObjectiveInfoCollection* Collection : ObjectiveInfoCollections)
	{
		SetupObjectivesByCollection(Collection, Assignees, OutObjectives);
	}
}

void UObjectiveTrackerComponent::SetupObjectivesByCollection(UObjectiveInfoCollection* InObjectiveInfoCollection, TArray<AActor*> Assignees, TArray<AObjective*>& OutObjectives, const FGameplayTagContainer& OptionalTags)
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	
	if (!IsValid(InObjectiveInfoCollection))
	{
		return;
	}

	TArray<FObjectiveInfo> ObjectiveInfos = InObjectiveInfoCollection->GetObjectiveInfos();

	AObjective* NewObjective = nullptr;

	for (const FObjectiveInfo& ObjectiveInfo : ObjectiveInfos)
	{
		//if we didn't specify any tags, then we just setup the objective
		if (OptionalTags.IsEmpty())
		{
			NewObjective = SetupObjective(ObjectiveInfo, Assignees);
			continue;
		}

		if (!ObjectiveInfo.ObjectiveClass)
		{
			continue;
		}

		AObjective* DefaultObjectiveObject = Cast<AObjective>(ObjectiveInfo.ObjectiveClass->GetDefaultObject());

		if (!DefaultObjectiveObject)
		{
			continue;
		}

		//if the objective has any of the optional tags, then we setup the objective
		if (DefaultObjectiveObject->ObjectiveTags.HasAny(OptionalTags))
		{
			NewObjective = SetupObjective(ObjectiveInfo,Assignees);
		}

		if (NewObjective)
		{
			OutObjectives.Add(NewObjective);
		}
	}
}

//sets up the objectives for this tracker
void UObjectiveTrackerComponent::SetupObjectivesByTags(const FGameplayTagContainer& ObjectiveTags, TArray<AActor*> Assignees, TArray<AObjective*>& OutObjectives)
{
	for (UObjectiveInfoCollection* Collection : ObjectiveInfoCollections)
	{
		SetupObjectivesByCollection(Collection, Assignees, OutObjectives, ObjectiveTags);
	}
}

AObjective* UObjectiveTrackerComponent::SetupObjective(const FObjectiveInfo& ObjectiveInfo, TArray<AActor*> Assignees)
{
	IObjectiveTrackerInterface* ObjectiveTrackerInterface = Cast<IObjectiveTrackerInterface>(GetOwner());

	if (!ObjectiveTrackerInterface)
	{
		return nullptr;
	}

	//find an exisiting objective of the same type if we already have one
	AObjective* NewObjective = FindObjective(ObjectiveInfo);

	//if we didn't find one, create a new one
	if (!NewObjective)
	{
		NewObjective = CreateObjective(ObjectiveInfo);
	}

	if (!NewObjective)
	{
		return nullptr;
	}
	
	for (AActor* Assignee : Assignees)
	{
		if (!Assignee)
		{
			continue;
		}
		
		AssignObjective(NewObjective, Assignee);
	}

	NewObjective->OnSetup();

	return NewObjective;
}

void UObjectiveTrackerComponent::BeginObjectivesByCollection(UObjectiveInfoCollection* InObjectiveInfoCollection, const FGameplayTagContainer& OptionalTags)
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	
	if (!IsValid(InObjectiveInfoCollection))
	{
		return;
	}

	const FGameplayTagContainer& AllObjectiveTags = InObjectiveInfoCollection->GetAllObjectiveTags();

	for (AObjective* Objective : Objectives)
	{
		if (Objective->ObjectiveTags.HasAny(AllObjectiveTags))
		{
			if (OptionalTags.IsEmpty())
			{
				BeginObjective(Objective);
				continue;
			}

			if (Objective->ObjectiveTags.HasAny(OptionalTags))
			{
				BeginObjective(Objective);
				continue;
			}
		}
	}
}

void UObjectiveTrackerComponent::BeginAllObjectives()
{
	for (AObjective* Objective : Objectives)
	{
		BeginObjective(Objective);
	}
}

void UObjectiveTrackerComponent::BeginObjectivesByTags(const FGameplayTagContainer& ObjectiveTags)
{
	for (AObjective* Objective : Objectives)
	{
		if (!Objective)
		{
			continue;
		}

		if (Objective->ObjectiveTags.HasAny(ObjectiveTags))
		{
			BeginObjective(Objective);
		}
	}
}
	
void UObjectiveTrackerComponent::BeginObjective(AObjective* Objective)
{
	if (!Objective)
	{
		return;
	}

	Objective->BeginAllAssignees();
}

void UObjectiveTrackerComponent::ProgressObjectives(AActor* Assignee, AActor* Instigator, const FGameplayTagContainer& ObjectiveTags, bool bSuccess)
{
	//must be authority to progress objectives
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	
	for (AObjective* Objective : Objectives)
	{
		if (!Objective)
		{
			continue;
		}

		if (!Objective->IsAssigned(Assignee))
		{
			continue;
		}

		if (!Objective->HasBegun(Assignee))
		{
			continue;
		}

		if (!Objective->GetObjectiveTags().HasAny(ObjectiveTags))
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

AObjective* UObjectiveTrackerComponent::FindObjective(const FObjectiveInfo& ObjectiveInfo)
{
	for (AObjective* Objective : Objectives)
	{
		if (!Objective)
		{
			continue;
		}

		AObjective* DefaultObjective = ObjectiveInfo.ObjectiveClass.GetDefaultObject();

		if (!DefaultObjective)
		{
			return nullptr;
		}

		if (Objective->ObjectiveTags.HasAll(DefaultObjective->ObjectiveTags))
		{
			return Objective;
		}
	}

	return nullptr;
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


