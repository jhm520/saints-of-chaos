// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCGameplayAbility_BoxSelect.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "SelectionSystem/SelectionSystemBlueprintLibrary.h"
#include "SOC/HUD/SOCHUD.h"
#include "SOC/HUD/Widgets/BoxSelectWidget.h"

USOCGameplayAbility_BoxSelect::USOCGameplayAbility_BoxSelect()
{
	
}

/** Actually activate ability, do not call this directly */
void USOCGameplayAbility_BoxSelect::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CommitAbility(Handle, ActorInfo, ActivationInfo);

	WaitTargetDataTask = UAbilityTask_WaitTargetData::WaitTargetData(this, "WaitTargetData", EGameplayTargetingConfirmation::Custom, TargetActorClass);

	if (!WaitTargetDataTask)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}

	WaitTargetDataTask->ValidData.AddDynamic(this, &USOCGameplayAbility_BoxSelect::OnTargetDataReady);
	WaitTargetDataTask->Cancelled.AddDynamic(this, &USOCGameplayAbility_BoxSelect::OnTargetDataCancelled);

	AGameplayAbilityTargetActor* SpawnedActor = nullptr;
	
	WaitTargetDataTask->BeginSpawningActor(this, TargetActorClass, SpawnedActor);
	WaitTargetDataTask->FinishSpawningActor(this, SpawnedActor);
	
	WaitTargetDataTask->ReadyForActivation();

	//BoxSelectInput(true);
}
	
/** Returns true if this ability can be activated right now. Has no side effects */
bool USOCGameplayAbility_BoxSelect::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void USOCGameplayAbility_BoxSelect::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
}

void USOCGameplayAbility_BoxSelect::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	//BoxSelectInput(false);

	if (WaitTargetDataTask)
	{
		WaitTargetDataTask->ExternalConfirm(true);
	}

	if (ActorInfo != NULL && ActorInfo->AvatarActor != NULL)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void USOCGameplayAbility_BoxSelect::BoxSelectInput(bool bPressed)
{
	APlayerController* PC = Cast<APlayerController>(GetActorInfo().PlayerController.Get());

	if (!PC)
	{
		return;
	}
	
	ASOCHUD* HUD = Cast<ASOCHUD>(PC->GetHUD());
	
	if (!HUD)
	{
		return;
	}

	if (HUD->GetBoxSelectWidget())
	{
		HUD->GetBoxSelectWidget()->OnBoxSelectInput(bPressed);
	}
}

#pragma region Targeting

void USOCGameplayAbility_BoxSelect::OnTargetDataReady(const FGameplayAbilityTargetDataHandle& Data)
{
	TArray<AActor*> Actors = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(Data, 0);

	if (Actors.Num() > 0)
	{
		//clear the current selection before selecting the new actor
		USelectionSystemBlueprintLibrary::ClearSelection(GetOwningActorFromActorInfo(), false);
		
		USelectionSystemBlueprintLibrary::SelectActors(GetOwningActorFromActorInfo(), Actors, false);
	}

	if (GetCurrentActorInfo() != NULL && GetCurrentActorInfo()->AvatarActor != NULL)
	{
		K2_EndAbility();
	}
}

void USOCGameplayAbility_BoxSelect::OnTargetDataCancelled(const FGameplayAbilityTargetDataHandle& Data)
{
	if (GetCurrentActorInfo() != NULL && GetCurrentActorInfo()->AvatarActor != NULL)
	{
		K2_CancelAbility();
	}
}

#pragma endregion


	