// © 2024 John Henry Miller. All rights reserved

#include "SOCGameplayAbility_SpawnMob.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "../Characters/SOCCharacter.h"

#include "Abilities/Tasks/AbilityTask_SpawnActor.h"

#pragma region Framework

/** Actually activate ability, do not call this directly */
void USOCGameplayAbility_SpawnMob::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// AActor* AvatarActor = GetAvatarActorFromActorInfo();
	//
	// if (!AvatarActor)
	// {
	// 	return;
	// }
	//
	// UAbilitySystemBlueprintLibrary::AbilityTargetDataFromLocations(AvatarActor->GetActorLocation(), AvatarActor->GetActorLocation());
	//
	// UAbilityTask_SpawnActor* SpawnActorTask = UAbilityTask_SpawnActor::SpawnActor(this, FGameplayAbilityTargetDataHandle(), MobClass);
	//
	// if (!SpawnActorTask)
	// {
	// 	return;
	// }
	//
	// SpawnActorTask->Success.AddDynamic(this, &USOCGameplayAbility_SpawnMob::OnMobSpawned);
	//
	// SpawnActorTask->ReadyForActivation();
	//
	//

	
}
	
/** Returns true if this ability can be activated right now. Has no side effects */
bool USOCGameplayAbility_SpawnMob::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}
#pragma endregion

#pragma region Spawn Mob

void USOCGameplayAbility_SpawnMob::OnMobSpawned(AActor* Mob)
{
	
}

#pragma endregion
