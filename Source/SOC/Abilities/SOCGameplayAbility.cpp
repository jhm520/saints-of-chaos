// © 2024 John Henry Miller. All rights reserved

#include "SOCGameplayAbility.h"

#pragma region Framework

/** Actually activate ability, do not call this directly */
void USOCGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
	
/** Returns true if this ability can be activated right now. Has no side effects */
bool USOCGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}
#pragma endregion

#pragma region Target Actors
	
/** Returns the actor that is the target of this ability */
AActor* USOCGameplayAbility::GetTargetActor() const
{
	IGameplayAbilityTargetActorInterface* TargetActorInterface = Cast<IGameplayAbilityTargetActorInterface>(GetActorInfo().AvatarActor.Get());

	if (!TargetActorInterface)
	{
		return nullptr;
	}
	
	return TargetActorInterface->GetTargetActor();
}

#pragma endregion