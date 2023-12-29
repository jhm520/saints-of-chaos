// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityCollection.h"
#include "AbilitySystemComponent.h"

void UGameplayAbilityCollection::GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAbilitySpecHandle>& BoundHandles, TArray<FGameplayAbilitySpecHandle>& DefaultBoundHandles) const
{
	if(!AbilitySystemComponent)
	{
		return;
	}
	
	for (const FInputGameplayAbilityInfo& AbilityInfo : BoundAbilities)
	{
		if (AbilityInfo.GameplayAbilityClass)
		{
			BoundHandles.Add(AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityInfo.GameplayAbilityClass, AbilityInfo.Level, (int32)AbilityInfo.Command)));
		}
	}

	for (const FDefaultGameplayAbilityInfo& AbilityInfo : DefaultAbilities)
	{
		if (AbilityInfo.GameplayAbilityClass)
		{
			DefaultBoundHandles.Add(AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityInfo.GameplayAbilityClass, AbilityInfo.Level, -1)));
		}
	}
}

void UGameplayAbilityCollection::RemoveAbilities(UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAbilitySpecHandle> BoundHandles, TArray<FGameplayAbilitySpecHandle> DefaultBoundHandles)
{
	for (const FGameplayAbilitySpecHandle& AbilityHandles : BoundHandles)
	{
		AbilitySystemComponent->ClearAbility(AbilityHandles);
	}

	for (const FGameplayAbilitySpecHandle& AbilityHandles : DefaultBoundHandles)
	{
		AbilitySystemComponent->ClearAbility(AbilityHandles);
	}
}
