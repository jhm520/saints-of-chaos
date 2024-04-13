// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "SOCGameplayAbility.h"
#include "SOCGameplayAbility_BoxSelect.generated.h"

class UAbilityTask_WaitTargetData;
class AGameplayAbilityTargetActor;
/**
 * 
 */
UCLASS()
class SOC_API USOCGameplayAbility_BoxSelect : public USOCGameplayAbility
{
	GENERATED_BODY()

#pragma region Framework
protected:
	USOCGameplayAbility_BoxSelect();
public:

	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	
	/** Returns true if this ability can be activated right now. Has no side effects */
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;

	/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

#pragma endregion
	
#pragma region BoxSelect

	void BoxSelectInput(bool bPressed);

#pragma endregion

	
#pragma region Targeting

	UPROPERTY()
	UAbilityTask_WaitTargetData* WaitTargetDataTask;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Targeting")
	TSubclassOf<AGameplayAbilityTargetActor> TargetActorClass;

	UFUNCTION()
	void OnTargetDataReady(const FGameplayAbilityTargetDataHandle& Data);

	UFUNCTION()
	void OnTargetDataCancelled(const FGameplayAbilityTargetDataHandle& Data);

#pragma endregion

};
