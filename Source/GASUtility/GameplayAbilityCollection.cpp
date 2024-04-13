// © 2024 John Henry Miller. All rights reserved

#include "GameplayAbilityCollection.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UGameplayAbilityCollection::GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAbilitySpecHandle>& BoundHandles, TArray<FGameplayAbilitySpecHandle>& DefaultBoundHandles) const
{
	if(!AbilitySystemComponent)
	{
		return;
	}

	if (!AbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		return;
	}
	
	for (const FInputGameplayAbilityInfo& AbilityInfo : BoundAbilities)
	{
		if (AbilityInfo.GameplayAbilityClass)
		{
			const FGameplayAbilitySpec& NewBoundSpec = FGameplayAbilitySpec(AbilityInfo.GameplayAbilityClass, AbilityInfo.Level, GetTypeHash(AbilityInfo.InputAction));
			
			BoundHandles.Add(AbilitySystemComponent->GiveAbility(NewBoundSpec));
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
