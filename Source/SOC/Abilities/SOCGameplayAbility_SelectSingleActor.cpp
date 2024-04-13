// © 2024 John Henry Miller. All rights reserved

#include "SOCGameplayAbility_SelectSingleActor.h"

#include "SelectionSystem/SelectionSystemBlueprintLibrary.h"

USOCGameplayAbility_SelectSingleActor::USOCGameplayAbility_SelectSingleActor()
{
	
}

/** Actually activate ability, do not call this directly */
void USOCGameplayAbility_SelectSingleActor::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CommitAbility(Handle, ActorInfo, ActivationInfo);

	//clear the current selection before selecting the new actor
	USelectionSystemBlueprintLibrary::ClearSelection(GetOwningActorFromActorInfo(), false);

	if (TriggerEventData)
	{
		const AActor* Actor = TriggerEventData->Target;

		USelectionSystemBlueprintLibrary::SelectActor(GetOwningActorFromActorInfo(), Actor, false);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
	
/** Returns true if this ability can be activated right now. Has no side effects */
bool USOCGameplayAbility_SelectSingleActor::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}