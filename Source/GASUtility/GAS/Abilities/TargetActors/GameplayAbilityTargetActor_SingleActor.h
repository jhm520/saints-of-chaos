// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GameplayAbilityTargetActor_SingleActor.generated.h"

/**
 * 
 */
UCLASS()
class GASUTILITY_API AGameplayAbilityTargetActor_SingleActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
protected:
	
	AGameplayAbilityTargetActor_SingleActor();
	
	FGameplayAbilityTargetDataHandle MakeTargetData(AActor* TargetActor) const;

	AActor* GetTargetActor();

	virtual void ConfirmTargetingAndContinue() override;

};
