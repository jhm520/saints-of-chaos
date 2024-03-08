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
	if (!GetAvatarActorFromActorInfo())
	{
		return false;
	}

	AActor* TargetActor = GetTargetActor();

	if (!TargetActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("USOCGameplayAbility_MeleeAttack::CanActivateAbility: TargetActor is null"));
		return false;
	}

	const FVector& AvatarLocation = GetAvatarActorFromActorInfo()->GetActorLocation();

	const FVector& TargetLocation = TargetActor->GetActorLocation();

	//if the target is out of range, we can't activate the ability
	if (AttackRange > 0.0f && FVector::DistSquared(AvatarLocation, TargetLocation) > FMath::Square(AttackRange))
	{
		UE_LOG(LogTemp, Warning, TEXT("USOCGameplayAbility_MeleeAttack::CanActivateAbility: Target is out of range"));
		return false;
	}
	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}
	
#pragma endregion