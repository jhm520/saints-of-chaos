// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCGameplayAbility_AutoCast.h"
#include "GASUtilityHelperLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"

#pragma region Framework
/** Actually activate ability, do not call this directly */
void USOCGameplayAbility_AutoCast::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CommitAbility(Handle, ActorInfo, ActivationInfo);

	CastAbility();

	QueueAbility();
	
}
	
/** Returns true if this ability can be activated right now. Has no side effects */
bool USOCGameplayAbility_AutoCast::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}
	
#pragma endregion

#pragma region Auto Cast
void USOCGameplayAbility_AutoCast::CastAbility()
{
	UAbilitySystemComponent* LocalASC = GetAbilitySystemComponentFromActorInfo();

	if (!LocalASC)
	{
		return;
	}
	
	LocalASC->TryActivateAbilityByClass(AbilityToAutoCast, true);
}

void USOCGameplayAbility_AutoCast::QueueAbility()
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();

	if (!AbilitySystemComponent)
	{
		return;
	}
	
	FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(AbilityToAutoCast);

	if (!AbilitySpec)
	{
		return;
	}

	if (!AbilitySpec->Ability)
	{
		return;
	}
	
	UGameplayEffect* GameplayEffect = AbilitySpec->Ability->GetCooldownGameplayEffect();

	if (!GameplayEffect)
	{
		return;
	}
	
	float TimeRemaining = 0.0f;
	float Duration = 0.0f;
	FGameplayTagContainer TagContainer;
	GameplayEffect->GetOwnedGameplayTags(TagContainer);
	
	UGASUtilityHelperLibrary::GetCooldownRemainingForTag(GetAbilitySystemComponentFromActorInfo(), TagContainer, TimeRemaining, Duration);


	//when the cooldown for the ability is removed, we will cast the ability again

	AbilitySystemComponent->OnAnyGameplayEffectRemovedDelegate().AddUObject(this, &USOCGameplayAbility_AutoCast::OnCooldownRemoved);
	
}

void USOCGameplayAbility_AutoCast::OnCooldownRemoved(const FActiveGameplayEffect& EffectHandle)
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();

	if (!AbilitySystemComponent)
	{
		return;
	}

	FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(AbilityToAutoCast);

	if (!AbilitySpec)
	{
		return;
	}

	if (!AbilitySpec->Ability)
	{
		return;
	}
	
	UGameplayEffect* GameplayEffect = AbilitySpec->Ability->GetCooldownGameplayEffect();

	//if the gameplay effect that was removed is the same as the cooldown gameplay effect, then we will cast the ability again
	const bool bCooldownRemoved = EffectHandle.Spec.Def == GameplayEffect;

	if (!bCooldownRemoved)
	{
		return;
	}
	
	AbilitySystemComponent->OnAnyGameplayEffectRemovedDelegate().RemoveAll(this);
	
	CastAbility();

	QueueAbility();
	
}


#pragma endregion 