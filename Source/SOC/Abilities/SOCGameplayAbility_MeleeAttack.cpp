// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCGameplayAbility_MeleeAttack.h"

	
#pragma region Framework
USOCGameplayAbility_MeleeAttack::USOCGameplayAbility_MeleeAttack()
{
	
}

/** Actually activate ability, do not call this directly */
void USOCGameplayAbility_MeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
	
/** Returns true if this ability can be activated right now. Has no side effects */
bool USOCGameplayAbility_MeleeAttack::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}
	
#pragma endregion