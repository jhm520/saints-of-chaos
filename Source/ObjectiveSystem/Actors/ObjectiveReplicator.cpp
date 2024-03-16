#include "ObjectiveReplicator.h"

#include "Objective.h"

#pragma region Framework

void FObjectiveReplicatorItem::PostReplicatedAdd(const FObjectiveReplicator& ObjectiveReplicator)
{
	UE_LOG(LogTemp, Warning, TEXT("PostReplicatedAdd: %d"), IsValid(ObjectiveReplicator.Objective));
	if(ObjectiveReplicator.Objective)
	{
		Cast<AObjective>(ObjectiveReplicator.Objective)->OnObjectiveStatusAdded(*this);	
	}
}

void FObjectiveReplicatorItem::PreReplicatedRemove(const FObjectiveReplicator& ObjectiveReplicator)
{
	UE_LOG(LogTemp, Warning, TEXT("PreReplicatedRemove: %d"), IsValid(ObjectiveReplicator.Objective));
	if(IsValid(ObjectiveReplicator.Objective))
	{
		Cast<AObjective>(ObjectiveReplicator.Objective)->OnObjectiveStatusRemoved(*this);	
	}
}

void FObjectiveReplicatorItem::PostReplicatedChange(const FObjectiveReplicator& ObjectiveReplicator)
{
	UE_LOG(LogTemp, Warning, TEXT("PostReplicatedChange: %d"), IsValid(ObjectiveReplicator.Objective));
	if(IsValid(ObjectiveReplicator.Objective))
	{
		Cast<AObjective>(ObjectiveReplicator.Objective)->OnObjectiveStatusChanged(*this);	
	}
}

FObjectiveReplicator::FObjectiveReplicator()
{
	Objective = nullptr;
}

bool FObjectiveReplicator::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
{
	return FastArrayDeltaSerialize<FObjectiveReplicatorItem, FObjectiveReplicator>(Items, DeltaParams, *this);
}

#pragma endregion
