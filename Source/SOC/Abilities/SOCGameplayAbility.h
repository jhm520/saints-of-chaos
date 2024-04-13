// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/GameplayAbilityBase.h"
#include "SOCGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API USOCGameplayAbility : public UGameplayAbilityBase, public IGameplayAbilityTargetActorInterface
{
	GENERATED_BODY()

public:
	/** Get default priority for running a task */
	virtual uint8 GetGameplayTaskDefaultPriority() const override { return FGameplayTasks::DefaultPriority; }

#pragma region Framework
public:

	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	
	/** Returns true if this ability can be activated right now. Has no side effects */
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;
	
#pragma endregion

#pragma region Target Actors
	
	/** Returns the actor that is the target of this ability */
	virtual AActor* GetTargetActor() const override;

#pragma endregion

};
