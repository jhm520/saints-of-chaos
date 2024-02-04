// Fill out your copyright notice in the Description page of Project Settings.

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
