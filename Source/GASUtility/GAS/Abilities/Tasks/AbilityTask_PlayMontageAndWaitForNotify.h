// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimInstance.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "CoreUtility/Animation/Notifies/AnimNotify_GameplayTag.h"
#include "CoreUtility/Timer/TimerHelper.h"
#include "AbilityTask_PlayMontageAndWaitForNotify.generated.h"

//struct to represent an AIController's current action
USTRUCT(BlueprintType)
struct GASUTILITY_API FMontageNotifyTrigger
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Notify")
	FGameplayTag GameplayTag = FGameplayTag::EmptyTag;

	UPROPERTY()
	FTimerHandle TimerHandle = FTimerHandle();

	FMontageNotifyTrigger(){}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMontageNotifyDelegate, FGameplayTag, Tag);


/** Ability task to simply play a montage. Many games will want to make a modified version of this task that looks for game-specific events */
UCLASS()
class GASUTILITY_API UAbilityTask_PlayMontageAndWaitForNotify : public UAbilityTask
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FMontageNotifyDelegate	OnCompleted;
	
	UPROPERTY(BlueprintAssignable)
	FMontageNotifyDelegate	OnBlendOut;
	
	UPROPERTY(BlueprintAssignable)
	FMontageNotifyDelegate	OnInterrupted;
	
	UPROPERTY(BlueprintAssignable)
	FMontageNotifyDelegate	OnCancelled;

	UPROPERTY(BlueprintAssignable)
	FMontageNotifyDelegate OnNotifyTriggered;

	UFUNCTION()
	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnMontageInterrupted();

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	/** 
	 * Start playing an animation montage on the avatar actor and wait for it to finish
	 * If StopWhenAbilityEnds is true, this montage will be aborted if the ability ends normally. It is always stopped when the ability is explicitly cancelled.
	 * On normal execution, OnBlendOut is called when the montage is blending out, and OnCompleted when it is completely done playing
	 * OnInterrupted is called if another montage overwrites this, and OnCancelled is called if the ability or task is cancelled
	 *
	 * @param TaskInstanceName Set to override the name of this task, for later querying
	 * @param MontageToPlay The montage to play on the character
	 * @param Rate Change to play the montage faster or slower
	 * @param StartSection If not empty, named montage section to start from
	 * @param bStopWhenAbilityEnds If true, this montage will be aborted if the ability ends normally. It is always stopped when the ability is explicitly cancelled
	 * @param AnimRootMotionTranslationScale Change to modify size of root motion or set to 0 to block it entirely
	 * @param StartTimeSeconds Starting time offset in montage, this will be overridden by StartSection if that is also set
	 */
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (DisplayName="PlayMontageAndWaitForNotify",
		HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_PlayMontageAndWaitForNotify* CreatePlayMontageAndWaitForNotifyProxy(UGameplayAbility* OwningAbility,
		FName TaskInstanceName, UAnimMontage* MontageToPlay, float Rate = 1.f, FName StartSection = NAME_None, bool bStopWhenAbilityEnds = true, float AnimRootMotionTranslationScale = 1.f, float StartTimeSeconds = 0.f, FGameplayTagContainer NotifyTags = FGameplayTagContainer());

	virtual void Activate() override;

	/** Called when the ability is asked to cancel from an outside node. What this means depends on the individual task. By default, this does nothing other than ending the task. */
	virtual void ExternalCancel() override;

	virtual FString GetDebugString() const override;

	void QueueNotifyEvents();

protected:

	virtual void OnDestroy(bool AbilityEnded) override;

	/** Checks if the ability is playing a montage and stops that montage, returns true if a montage was stopped, false if not. */
	bool StopPlayingMontage();

	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;
	FDelegateHandle InterruptedHandle;

	UPROPERTY()
	FGameplayTagContainer NotifyTags;

	UPROPERTY()
	TSubclassOf<UAnimNotify> NotifyClass;
	
	UPROPERTY()
	TObjectPtr<UAnimMontage> MontageToPlay;

	UPROPERTY()
	float Rate;

	UPROPERTY()
	FName StartSection;

	UPROPERTY()
	float AnimRootMotionTranslationScale;

	UPROPERTY()
	float StartTimeSeconds;

	UPROPERTY()
	bool bStopWhenAbilityEnds;
	
	UPROPERTY()
	TArray<FMontageNotifyTrigger> NotifyTriggers;

	FOnTimerHelperFinishedDelegate TimerHelperDelegate;

	UPROPERTY()
	TArray<TObjectPtr<UTimerHelper>> TimerHelpers;

	UFUNCTION()
	void OnTimerHelperNotify(UTimerHelper* TimerHelper);
};
