// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOCGameplayAbility.h"
#include "SOCGameplayAbility_AutoCast.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API USOCGameplayAbility_AutoCast : public USOCGameplayAbility
{
	GENERATED_BODY()

#pragma region Framework
public:

	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	
	/** Returns true if this ability can be activated right now. Has no side effects */
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;
	
#pragma endregion

#pragma region Auto Cast
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Auto Cast")
	TSubclassOf<USOCGameplayAbility> AbilityToAutoCast;

	UFUNCTION()
	void CastAbility();

	UFUNCTION()
	void QueueAbility();

	UFUNCTION()
	void OnCooldownRemoved(const FActiveGameplayEffect& EffectHandle);
#pragma endregion 
	
};
