// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehaviorManager.h"

#include "SOCAIBehavior.h"
#include "SOCAIDataAsset.h"

ASOCAIBehaviorManager::ASOCAIBehaviorManager(const FObjectInitializer& ObjectInitializer)
{
	bAlwaysRelevant = true;
}

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

void ASOCAIBehaviorManager::BeginPlay()
{

	//Create all behavior objects
	TArray<FGameplayTag> BehaviorTags;

	for (TSubclassOf<USOCAIBehavior> BehaviorClass : BehaviorClassArray)
	{
		BehaviorClass.GetDefaultObject()->GetBehaviorTag();
		
		USOCAIBehavior* NewBehavior = NewObject<USOCAIBehavior>(this, BehaviorClass);

		if (NewBehavior)
		{
			BehaviorMap.Add(BehaviorClass.GetDefaultObject()->GetBehaviorTag(), NewBehavior);
		}
	}
	
	Super::BeginPlay();
}

void ASOCAIBehaviorManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

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
