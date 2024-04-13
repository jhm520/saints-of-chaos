// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "SOCGameplayAbility.h"
#include "SOCGameplayAbility_SelectSingleActor.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API USOCGameplayAbility_SelectSingleActor : public USOCGameplayAbility
{
	GENERATED_BODY()
	
#pragma region Framework
protected:
	USOCGameplayAbility_SelectSingleActor();
public:

	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	
	/** Returns true if this ability can be activated right now. Has no side effects */
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;
	
#pragma endregion
};
