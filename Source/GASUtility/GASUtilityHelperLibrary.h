// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayAbilitySpec.h"
#include "Abilities/GameplayAbility.h"
#include "GASUtilityHelperLibrary.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class GASUTILITY_API UGASUtilityHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	// Returns the cooldown remaining, and total duration, for the cooldown tag
	//Target is the AbilitySystem that has the cooldown tags currently applied
	//InCooldownTags is the tags to check for cooldowns
	//TimeRemaining is the time remaining on the cooldown tag
	//CooldownDuration is the total duration of the cooldown tag
	UFUNCTION(BlueprintCallable, Category = "GAS")
	static bool GetCooldownRemainingForTag(UAbilitySystemComponent* Target, FGameplayTagContainer InCooldownTags, float& TimeRemaining, float& CooldownDuration);

	/** Returns an ability spec that corresponds to a superclass of the given ability class. If modifying call MarkAbilitySpecDirty */
	static FGameplayAbilitySpec* FindAbilitySpecFromSuperClass(UAbilitySystemComponent* InASC, TSubclassOf<UGameplayAbility> InAbilitySuperClass);


};
