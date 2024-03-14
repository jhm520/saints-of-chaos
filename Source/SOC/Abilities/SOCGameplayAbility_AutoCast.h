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
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	/** Returns true if this ability can be activated right now. Has no side effects */
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

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
	void TryCastingAbilityAgain();

	UPROPERTY()
	FTimerHandle TimerHandle_TryAgain;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Auto Cast")
	float TryAgainInterval = 0.25f;

	UFUNCTION()
	void OnCooldownRemoved(const FActiveGameplayEffect& EffectHandle);

	UFUNCTION()
	void CancelAutoCast();
#pragma endregion 
	
};
