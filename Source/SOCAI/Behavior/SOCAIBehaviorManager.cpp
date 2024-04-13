// © 2024 John Henry Miller. All rights reserved

#include "SOCAIBehaviorManager.h"

#include "SOCAIBehavior.h"
#include "SOCAI/Data/SOCAIDataAsset.h"
#include "SOCAI/Subsystem/SOCAIBehaviorSubsystem.h"

#pragma region Framework
ASOCAIBehaviorManager::ASOCAIBehaviorManager(const FObjectInitializer& ObjectInitializer)
{
	bAlwaysRelevant = true;
	bReplicates = true;
}

void ASOCAIBehaviorManager::BeginPlay()
{
	SetupBehaviorTree();
	
	Super::BeginPlay();

	USOCAIBehaviorSubsystem* BehaviorSubsystem = USOCAIBehaviorSubsystem::Get(this);

	if (BehaviorSubsystem)
	{
		BehaviorSubsystem->Register(this);
	}
}

void ASOCAIBehaviorManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	USOCAIBehaviorSubsystem* BehaviorSubsystem = USOCAIBehaviorSubsystem::Get(this);

	if (BehaviorSubsystem)
	{
		BehaviorSubsystem->Unregister(this);
	}

	TArray<TObjectPtr<USOCAIBehavior>> Behaviors;
	BehaviorMap.GenerateValueArray(Behaviors);

	for (USOCAIBehavior* Behavior : Behaviors)
	{
		if (!Behavior)
		{
			continue;
		}

		Behavior->ConditionalBeginDestroy();
	}
	
}
#pragma endregion

#pragma region Behavior

USOCAIBehavior* ASOCAIBehaviorManager::GetBehavior(const FGameplayTag& InBehaviorTag)
{
	if (BehaviorMap.IsEmpty())
	{
		return nullptr;
	}

	const TObjectPtr<USOCAIBehavior>* BehaviorPtr = BehaviorMap.Find(InBehaviorTag);

	if (!BehaviorPtr)
	{
		return nullptr;
	}

	return *BehaviorPtr;
	
}

void ASOCAIBehaviorManager::SetupBehaviorTree()
{
	if (!SOCAIDataAsset)
	{
		return;
	}
	
	//Create all behavior objects
	TArray<FGameplayTag> BehaviorTags;

	for (TSubclassOf<USOCAIBehavior> BehaviorClass : SOCAIDataAsset->GetBehaviorClasses())
	{
		USOCAIBehavior* NewBehavior = NewObject<USOCAIBehavior>(this, BehaviorClass);

		if (NewBehavior)
		{
			BehaviorMap.Add(BehaviorClass.GetDefaultObject()->GetBehaviorTag(), NewBehavior);
		}
	}

	//Setup the behavior linked tree by linking all the behavior objects with Parents and Children

	TArray<TObjectPtr<USOCAIBehavior>> BehaviorArray;
	BehaviorMap.GenerateValueArray(BehaviorArray);

	for (TObjectPtr<USOCAIBehavior> Behavior : BehaviorArray)
	{
		if (!IsValid(Behavior))
		{
			continue;
		}

		USOCAIBehavior* ParentBehavior = GetBehavior(Behavior->GetParentBehaviorTag());

		if (ParentBehavior)
		{
			Behavior->SetParentBehavior(ParentBehavior);
		}

		for (const FGameplayTag& ChildBehaviorTag : Behavior->GetChildBehaviorTags())
		{
			USOCAIBehavior* ChildBehavior = GetBehavior(ChildBehaviorTag);

			if (!ChildBehavior)
			{
				continue;
			}

			Behavior->AddChildBehavior(ChildBehavior);
		}
	}
}
#pragma endregion
