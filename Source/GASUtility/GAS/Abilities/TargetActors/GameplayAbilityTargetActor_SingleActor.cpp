// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityTargetActor_SingleActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayAbilityTargetActorInterface.h"
#include "Abilities/GameplayAbility.h"

AGameplayAbilityTargetActor_SingleActor::AGameplayAbilityTargetActor_SingleActor()
{
	ShouldProduceTargetDataOnServer = true;
}

FGameplayAbilityTargetDataHandle AGameplayAbilityTargetActor_SingleActor::MakeTargetData(AActor* TargetActor) const
{
	return UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(TargetActor);
}

AActor* AGameplayAbilityTargetActor_SingleActor::GetTargetActor()
{
	if (!OwningAbility)
	{
		return nullptr;
	}
	
	IGameplayAbilityTargetActorInterface* TargetActorInterface = Cast<IGameplayAbilityTargetActorInterface>(OwningAbility);

	if (!TargetActorInterface)
	{
		return nullptr;
	}

	return TargetActorInterface->GetTargetActor();
}

void AGameplayAbilityTargetActor_SingleActor::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		bDebug = false;
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(GetTargetActor());
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}

