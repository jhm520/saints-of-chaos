// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehavior.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "SOCAI/Components/SOCAIBehaviorComponent.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"

bool USOCAIBehavior::CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction) const
{
	//add the tag to the behavior path, letting the other nodes know that we've traversed this node
	BehaviorPath.AddTag(GetBehaviorTag());
	
	//if we passed in a ParentAction with a specified behavior tag, decide the action on that behavior instead
	if (GetChildBehaviorTags().HasTagExact(InParentAction.BehaviorTag))
	{
		USOCAIBehavior* ChildBehavior = GetChildBehavior(InParentAction.BehaviorTag);

		if (ChildBehavior)
		{
			const bool bChildSuccess = ChildBehavior->CalculateCurrentAction(InActor, OutAction,BehaviorPath, InParentAction);
		
			if (bChildSuccess)
			{
				return true;
			}
		}
	}

	TArray<FGameplayTag> GameplayTagArray;
	GetChildBehaviorTags().GetGameplayTagArray(GameplayTagArray);
	
	//Check each of this node's children and check if we should do that action instead
	for (const FGameplayTag& LocalBehaviorTag : GameplayTagArray)
	{
		//Do not traverse nodes that we've already traversed on this path to avoid infinite looping
		if (BehaviorPath.HasTagExact(LocalBehaviorTag))
		{
			continue;
		}
		
		USOCAIBehavior* ChildBehavior = GetChildBehavior(LocalBehaviorTag);

		if (!ChildBehavior)
		{
			continue;
		}
		
		const bool bChildSuccess = ChildBehavior->CalculateCurrentAction(InActor, OutAction,BehaviorPath, InParentAction);
		
		if (bChildSuccess)
		{
			return true;
		}
	}

	//If its already decided that we're executing an action, by either the parent or a subclass, return true
	if (InParentAction.ActionTag != SOCAIActionTags::None)
	{
		return true;
	}


	if (OutAction.ActionTag != SOCAIActionTags::None)
	{
		return true;
	}
	
	return K2_CalculateCurrentAction(InActor, OutAction,BehaviorPath, InParentAction);

}

AActor* USOCAIBehavior::GetDirector(const AActor* InBehaviorActor) const
{
	const ISOCAIBehaviorInterface* BehaviorInterface = Cast<ISOCAIBehaviorInterface>(InBehaviorActor);

	if (!BehaviorInterface)
	{
		return nullptr;
	}

	USOCAIBehaviorComponent* BehaviorComponent = BehaviorInterface->GetBehaviorComponent();

	if (!BehaviorComponent)
	{
		return nullptr;
	}

	return BehaviorComponent->GetDirector();
}

void USOCAIBehavior::AddChildBehavior(USOCAIBehavior* InChildBehavior)
{
	if (!InChildBehavior)
	{
		return;
	}

	ChildBehaviorMap.Add(InChildBehavior->BehaviorTag, InChildBehavior);
}

USOCAIBehavior* USOCAIBehavior::GetChildBehavior(const FGameplayTag& InBehaviorTag) const
{
	if (GetChildBehaviorTags().IsEmpty())
	{
		return nullptr;
	}

	const TObjectPtr<USOCAIBehavior>* BehaviorPtr = ChildBehaviorMap.Find(InBehaviorTag);

	if (!BehaviorPtr)
	{
		return nullptr;
	}

	return *BehaviorPtr;
}

USOCAIBehavior::USOCAIBehavior()
{
	
}

void USOCAIBehavior::OnEnteredBehavior(AActor* InBehaviorActor, const FSOCAIAction& InEnteredBehaviorAction, const FSOCAIAction& InExitedBehaviorAction) const
{
	if (!InBehaviorActor || !InBehaviorActor->Implements<USOCAIBehaviorInterface>())
	{
		return;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InBehaviorActor);

	for (const FBehaviorGameplayAbility& LocalAbility : BehaviorGameplayAbilities)
	{
		if (LocalAbility.ActivationMode == EBehaviorGameplayAbilityActivationMode::OnEnter
			|| LocalAbility.ActivationMode == EBehaviorGameplayAbilityActivationMode::OnEnterAndExit)
		{
			if (ASC)
			{
				ASC->TryActivateAbilityByClass(LocalAbility.GameplayAbilityClass, true);
			}
		}

		if (LocalAbility.DeactivationMode == EBehaviorGameplayAbilityDeactivationMode::OnEnter
			|| LocalAbility.DeactivationMode == EBehaviorGameplayAbilityDeactivationMode::OnEnterAndExit)
		{
			if (ASC)
			{
				FGameplayAbilitySpec* AbilitySpec = ASC->FindAbilitySpecFromClass(LocalAbility.GameplayAbilityClass);

				if (AbilitySpec)
				{
					ASC->CancelAbility(AbilitySpec->Ability);
				}
			}
		}
	}

	ISOCAIBehaviorInterface::Execute_OnEnteredBehavior(InBehaviorActor, InEnteredBehaviorAction, InExitedBehaviorAction);

	
	K2_OnEnteredBehavior(InBehaviorActor, InEnteredBehaviorAction, InExitedBehaviorAction);
}

void USOCAIBehavior::OnExitedBehavior(AActor* InBehaviorActor, const FSOCAIAction& InExitedBehaviorAction, const FSOCAIAction& InEnteredBehaviorAction) const
{
	if (!InBehaviorActor || !InBehaviorActor->Implements<USOCAIBehaviorInterface>())
	{
		return;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InBehaviorActor);

	for (const FBehaviorGameplayAbility& LocalAbility : BehaviorGameplayAbilities)
	{
		if (LocalAbility.ActivationMode == EBehaviorGameplayAbilityActivationMode::OnExit
			|| LocalAbility.ActivationMode == EBehaviorGameplayAbilityActivationMode::OnEnterAndExit)
		{
			if (ASC)
			{
				ASC->TryActivateAbilityByClass(LocalAbility.GameplayAbilityClass, true);
			}
		}

		if (LocalAbility.DeactivationMode == EBehaviorGameplayAbilityDeactivationMode::OnExit
			|| LocalAbility.DeactivationMode == EBehaviorGameplayAbilityDeactivationMode::OnEnterAndExit)
		{
			if (ASC)
			{
				FGameplayAbilitySpec* AbilitySpec = ASC->FindAbilitySpecFromClass(LocalAbility.GameplayAbilityClass);

				if (AbilitySpec)
				{
					ASC->CancelAbility(AbilitySpec->Ability);
				}
			}
		}
	}

	ISOCAIBehaviorInterface::Execute_OnExitedBehavior(InBehaviorActor, InEnteredBehaviorAction, InExitedBehaviorAction);
	
	K2_OnExitedBehavior(InBehaviorActor, InExitedBehaviorAction, InEnteredBehaviorAction);
}
