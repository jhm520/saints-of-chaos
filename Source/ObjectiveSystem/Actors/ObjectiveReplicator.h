#pragma once

#include "Net/Serialization/FastArraySerializer.h"
#include "ObjectiveSystem/DataAssets/ObjectiveInfoCollection.h"
#include "ObjectiveReplicator.generated.h"

/*
 * This file stores the networking part of the inventory slot using FFastArraySerializer
 */


USTRUCT(BlueprintType)
struct OBJECTIVESYSTEM_API FObjectiveReplicatorItem : public FFastArraySerializerItem
{
	GENERATED_BODY()
public:
	FObjectiveReplicatorItem()
	{
		ObjectiveStatus = FObjectiveStatus();
	}

	FObjectiveReplicatorItem(const FObjectiveStatus& InObjectiveStatus)
	{
		ObjectiveStatus = InObjectiveStatus;
	}
	
	void PreReplicatedRemove(const struct FObjectiveReplicator& ObjectiveReplicator);
	void PostReplicatedAdd(const struct FObjectiveReplicator& ObjectiveReplicator);
	void PostReplicatedChange(const struct FObjectiveReplicator& ObjectiveReplicator);
	

	// The inventory item in this slot
	UPROPERTY(BlueprintReadOnly)
	FObjectiveStatus ObjectiveStatus;

	bool operator==(const FObjectiveReplicatorItem& Other) const
	{
		return ObjectiveStatus.Assignee == Other.ObjectiveStatus.Assignee;
	}
};

USTRUCT()
struct OBJECTIVESYSTEM_API FObjectiveReplicator : public FFastArraySerializer
{
	GENERATED_BODY()
public:
	FObjectiveReplicator();
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams);

	// Items in the inventory
	UPROPERTY()
	TArray<FObjectiveReplicatorItem> Items;

	// Owning object
	UPROPERTY()
	TObjectPtr<class AObjective> Objective;
};

// Tell UE5 that we're using these structs for network delta serialization
template <>
struct TStructOpsTypeTraits<FObjectiveReplicator> : public TStructOpsTypeTraitsBase2<FObjectiveReplicator>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};
