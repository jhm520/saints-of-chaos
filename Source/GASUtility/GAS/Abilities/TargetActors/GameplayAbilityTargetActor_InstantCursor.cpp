// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityTargetActor_InstantCursor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayAbilityTargetActorInterface.h"
#include "Abilities/GameplayAbility.h"

AGameplayAbilityTargetActor_InstantCursor::AGameplayAbilityTargetActor_InstantCursor()
{
	ShouldProduceTargetDataOnServer = false;
}

FGameplayAbilityTargetDataHandle AGameplayAbilityTargetActor_InstantCursor::MakeTargetData(const FHitResult& HitResult) const
{
	return UAbilitySystemBlueprintLibrary::AbilityTargetDataFromHitResult(HitResult);
}

void AGameplayAbilityTargetActor_InstantCursor::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	
	bDebug = false;
	FGameplayAbilityTargetDataHandle Handle = MakeTargetData(PerformTrace());
	TargetDataReadyDelegate.Broadcast(Handle);
}

FHitResult AGameplayAbilityTargetActor_InstantCursor::PerformTrace_Implementation()
{
	if (!OwningAbility)
	{
		return FHitResult();
	}
	
	APlayerController* PC = OwningAbility->GetCurrentActorInfo()->PlayerController.Get();
	
	if(!PC)
	{
		return FHitResult();
	}
	
	if(!PC->IsLocalPlayerController())
	{
		return FHitResult();
	}

	FHitResult ReturnHitResult;

	PC->GetHitResultUnderCursorByChannel(CursorTraceChannel, bTraceComplex, ReturnHitResult);
	
	return ReturnHitResult;
}