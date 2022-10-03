// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehaviorManager.h"

#include "SOCAIBehavior.h"
#include "SOCAIDataAsset.h"

void ASOCAIBehaviorManager::BeginPlay()
{
	Super::BeginPlay();

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
