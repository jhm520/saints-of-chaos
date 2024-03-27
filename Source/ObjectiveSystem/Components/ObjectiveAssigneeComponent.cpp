//


#include "ObjectiveAssigneeComponent.h"

#include "ObjectiveSystem/ObjectiveSubsystem.h"
#include "ObjectiveSystem/Actors/Objective.h"

#pragma region Framework

// Sets default values for this component's properties
UObjectiveAssigneeComponent::UObjectiveAssigneeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UObjectiveAssigneeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UObjectiveAssigneeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// ...
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void UObjectiveAssigneeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#pragma endregion

#pragma region Objective System

void UObjectiveAssigneeComponent::ProgressObjectivesForAssigneeByTags(AActor* Assignee, const FGameplayTagContainer& ObjectiveTags, bool bSuccess)
{
	if (!GetOwner()->HasAuthority())
	{
		Server_ProgressObjectivesForAssigneeByTags(Assignee, ObjectiveTags, bSuccess);
		return;
	}
	
	UObjectiveSubsystem* ObjectiveSubsystem = UObjectiveSubsystem::Get(Assignee->GetWorld());

	if (!ObjectiveSubsystem)
	{
		return;
	}

	ObjectiveSubsystem->ProgressAssignedObjectives(Assignee, ObjectiveTags, bSuccess);
}

void UObjectiveAssigneeComponent::Server_ProgressObjectivesForAssigneeByTags_Implementation(AActor* Assignee, const FGameplayTagContainer& ObjectiveTags, bool bSuccess)
{
	ProgressObjectivesForAssigneeByTags(Assignee, ObjectiveTags, bSuccess);
}



#pragma endregion

#pragma region Replication

void UObjectiveAssigneeComponent::ReplicateAssigneeObjectiveStatuses(AObjective* Objective)
{
	if (!IsValid(Objective))
	{
		return;
	}

	Objective->ReplicateObjectiveStatuses();
}

#pragma endregion

