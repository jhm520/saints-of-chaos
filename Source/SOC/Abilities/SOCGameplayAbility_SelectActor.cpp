// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCGameplayAbility_SelectActor.h"

#include "SelectionSystem/SelectionSystemBlueprintLibrary.h"

USOCGameplayAbility_SelectActor::USOCGameplayAbility_SelectActor()
{
	
}

/** Actually activate ability, do not call this directly */
void USOCGameplayAbility_SelectActor::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const AActor* Actor = TriggerEventData->Target;

	USelectionSystemBlueprintLibrary::SelectActor(GetOwningActorFromActorInfo(), Actor, false);
}
	
/** Returns true if this ability can be activated right now. Has no side effects */
bool USOCGameplayAbility_SelectActor::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}
	