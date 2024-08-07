// © 2024 John Henry Miller. All rights reserved

#include "SOCGameplayAbility_ContextCommand.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "CommandSystem/CommandSystemBlueprintLibrary.h"
#include "CoreUtility/Attitude/AttitudeInterface.h"
#include "GAS/Abilities/TargetActors/GameplayAbilityTargetActor_InstantCursor.h"
#include "SelectionSystem/SelectionSystemBlueprintLibrary.h"
#include "SelectionSystem/Components/SelectableComponent.h"
#include "SelectionSystem/Components/SelectorComponent.h"
#include "SelectionSystem/Interfaces/SelectableInterface.h"
#include "SelectionSystem/Interfaces/SelectorInterface.h"

#pragma region Framework

USOCGameplayAbility_ContextCommand::USOCGameplayAbility_ContextCommand()
{
	TargetActorClass = AGameplayAbilityTargetActor_InstantCursor::StaticClass();
}

/** Actually activate ability, do not call this directly */
void USOCGameplayAbility_ContextCommand::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	

	UAbilityTask_WaitTargetData* WaitTargetDataTask = UAbilityTask_WaitTargetData::WaitTargetData(this, "WaitTargetData", EGameplayTargetingConfirmation::Instant, TargetActorClass);

	if (!WaitTargetDataTask)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}

	WaitTargetDataTask->ValidData.AddDynamic(this, &USOCGameplayAbility_ContextCommand::OnTargetDataReady);
	WaitTargetDataTask->Cancelled.AddDynamic(this, &USOCGameplayAbility_ContextCommand::OnTargetDataCancelled);

	AGameplayAbilityTargetActor* SpawnedActor = nullptr;
	
	WaitTargetDataTask->BeginSpawningActor(this, TargetActorClass, SpawnedActor);
	WaitTargetDataTask->FinishSpawningActor(this, SpawnedActor);

	WaitTargetDataTask->ReadyForActivation();
}
	
/** Returns true if this ability can be activated right now. Has no side effects */
bool USOCGameplayAbility_ContextCommand::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	//Check if the selected units are friendly
	TArray<USelectableComponent*> Selected;

	USelectionSystemBlueprintLibrary::GetSelectedComponents(GetCurrentActorInfo()->AvatarActor.Get(), Selected);

	if (Selected.IsEmpty())
	{
		return false;
	}

	for (USelectableComponent* Selectable : Selected)
	{
		if (!Selectable)
		{
			return false;
		}

		AActor* SelectableOwner = Selectable->GetOwner();

		if (!SelectableOwner)
		{
			return false;
		}

		if (!SelectableOwner->Implements<UAttitudeInterface>())
		{
			return false;
		}

		// const EAttitude Attitude = IAttitudeInterface::Execute_GetAttitudeTowards(GetCurrentActorInfo()->AvatarActor.Get(), SelectableOwner);
		//
		// if (Attitude != EAttitude::Friendly)
		// {
		// 	return false;
		// }
	}
	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
void USOCGameplayAbility_ContextCommand::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USOCGameplayAbility_ContextCommand::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	
	if (ActorInfo != NULL && ActorInfo->AvatarActor != NULL)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}
	
#pragma endregion

#pragma region Targeting

void USOCGameplayAbility_ContextCommand::OnTargetDataReady(const FGameplayAbilityTargetDataHandle& Data)
{
	TArray<USelectableComponent*> Selected;
	
	const FHitResult& HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(Data, 0);
	
	USelectionSystemBlueprintLibrary::GetSelectedComponents(GetCurrentActorInfo()->AvatarActor.Get(), Selected);

	if (Selected.IsEmpty())
	{
		return;
	}
	
	for  (USelectableComponent* Selectable : Selected)
	{
		if (!Selectable)
		{
			continue;
		}

		AActor* SelectableOwner = Selectable->GetOwner();

		if (!SelectableOwner)
		{
			continue;
		}

		if (!SelectableOwner->Implements<UAttitudeInterface>())
		{
			continue;
		}

		//make sure we only command friendly units
		const EAttitude Attitude = IAttitudeInterface::Execute_GetAttitudeTowards(GetCurrentActorInfo()->AvatarActor.Get(), SelectableOwner);

		if (Attitude != EAttitude::Friendly)
		{
			continue;
		}
		
		AActor* SelectedActor = Selectable->GetOwner();

		if (!SelectedActor)
		{
			continue;
		}

		ISelectableInterface* HitActorSelectable = Cast<ISelectableInterface>(HitResult.GetActor());
		
		//Order the selected unit
		FCommandInstance NewCommand;
		if (HitActorSelectable && HitResult.GetActor()->Implements<UAttitudeInterface>() && IAttitudeInterface::Execute_GetAttitudeTowards(GetCurrentActorInfo()->AvatarActor.Get(), HitResult.GetActor()) == EAttitude::Hostile)
		{
			NewCommand = UCommandSystemBlueprintLibrary::MakeCommand(GetCurrentActorInfo()->AvatarActor.Get(), AttackCommandTag, HitResult.GetActor(), HitResult.ImpactPoint);
		}
		else
		{
			NewCommand = UCommandSystemBlueprintLibrary::MakeCommand(GetCurrentActorInfo()->AvatarActor.Get(), MovementCommandTag, HitActorSelectable ? HitResult.GetActor() : nullptr, HitResult.ImpactPoint);
		}

		if (NewCommand.IsValid())
		{
			UCommandSystemBlueprintLibrary::CommandActor(GetCurrentActorInfo()->AvatarActor.Get(), SelectedActor, NewCommand, bQueueCommand);
		}
	}
}

void USOCGameplayAbility_ContextCommand::OnTargetDataCancelled(const FGameplayAbilityTargetDataHandle& Data)
{
	if (GetCurrentActorInfo() != NULL && GetCurrentActorInfo()->AvatarActor != NULL)
	{
		K2_CancelAbility();
	}
}

#pragma endregion