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
void UObjectiveTrackerComponent::SetupAllObjectives()
{
	for (UObjectiveInfoCollection* Collection : ObjectiveInfoCollections)
	{
		SetupObjectivesByCollection(Collection);
	}
}

void UObjectiveTrackerComponent::SetupObjectivesByCollection(UObjectiveInfoCollection* InObjectiveInfoCollection, const FGameplayTagContainer& OptionalTags)
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

	for (const FObjectiveInfo& ObjectiveInfo : ObjectiveInfos)
	{
		//if we didn't specify any tags, then we just setup the objective
		if (OptionalTags.IsEmpty())
		{
			SetupObjective(ObjectiveInfo);
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
			SetupObjective(ObjectiveInfo);
		}
	}
}

//sets up the objectives for this tracker
void UObjectiveTrackerComponent::SetupObjectivesByTags(const FGameplayTagContainer& ObjectiveTags)
{
	for (UObjectiveInfoCollection* Collection : ObjectiveInfoCollections)
	{
		SetupObjectivesByCollection(Collection, ObjectiveTags);
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

	Objective->Begin();
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


