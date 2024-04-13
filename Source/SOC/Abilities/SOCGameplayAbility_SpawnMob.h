// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "SOCGameplayAbility.h"
#include "SOCGameplayAbility_SpawnMob.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API USOCGameplayAbility_SpawnMob : public USOCGameplayAbility
{
	GENERATED_BODY()
#pragma region Framework
public:

	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	
	/** Returns true if this ability can be activated right now. Has no side effects */
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;
	
#pragma endregion
	
#pragma region Spawn Mob

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Mob")
	TSubclassOf<class ASOCCharacter> MobClass;

	UFUNCTION()
	void OnMobSpawned(AActor* Mob);

#pragma endregion

};
