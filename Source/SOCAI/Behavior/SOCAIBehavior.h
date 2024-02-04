// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../SOCAIGameplayTags.h"
#include "SOCAIBehavior.generated.h"

class UGameplayAbility;

//struct to represent an AIController's current action
USTRUCT(BlueprintType)
struct SOCAI_API FSOCAIAction
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Behavior")
	FGameplayTag ActionTag = SOCAIActionTags::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Behavior")
	FGameplayTag BehaviorTag = SOCAIBehaviorTags::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Behavior")
	FVector TargetLocation{ForceInit};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Behavior")
	TObjectPtr<AActor> TargetActor = nullptr;

	FSOCAIAction(){}
};

UENUM(BlueprintType)
enum class EBehaviorGameplayAbilityActivationMode : uint8
{
	//The ability will be activated when the behavior is entered
	OnEnter,
	//The ability will be activated when the behavior is exited
	OnExit,
	//The ability will be activated when the behavior is entered and exited
	OnEnterAndExit,
	None
};

UENUM(BlueprintType)
enum class EBehaviorGameplayAbilityDeactivationMode : uint8
{
	//The ability will be deactivated when the behavior is entered
	OnEnter,
	//The ability will be deactivated when the behavior is exited
	OnExit,
	//The ability will be deactivated when the behavior is entered and exited
	OnEnterAndExit,
	None
};

//struct to represent an AIController's current action
USTRUCT(BlueprintType)
struct SOCAI_API FBehaviorGameplayAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	EBehaviorGameplayAbilityActivationMode ActivationMode = EBehaviorGameplayAbilityActivationMode::OnEnter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	EBehaviorGameplayAbilityDeactivationMode DeactivationMode = EBehaviorGameplayAbilityDeactivationMode::OnExit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	TSubclassOf<UGameplayAbility> GameplayAbilityClass;

};

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class SOCAI_API USOCAIBehavior : public UObject
{
	GENERATED_BODY()

#pragma region Framework
protected:
	USOCAIBehavior();
#pragma endregion

#pragma region Initialization
public:
	UFUNCTION()
	void SetParentBehavior(USOCAIBehavior* InParentBehavior){ParentBehavior = InParentBehavior;};

	UFUNCTION()
	void AddChildBehavior(USOCAIBehavior* InChildBehavior);
#pragma endregion
	
#pragma region Properties
public:
	UFUNCTION()
	USOCAIBehavior* GetChildBehavior(const FGameplayTag& InBehaviorTag) const;
	
	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const FGameplayTag& GetBehaviorTag() const {return BehaviorTag;};
	
	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const FGameplayTag& GetParentBehaviorTag() const {return ParentBehaviorTag;};

	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const FGameplayTagContainer& GetChildBehaviorTags() const{return ChildBehaviorTags;};
protected:
	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	FGameplayTag ParentBehaviorTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	FGameplayTag BehaviorTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	FGameplayTagContainer ChildBehaviorTags;

	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TObjectPtr<USOCAIBehavior> ParentBehavior = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TMap<FGameplayTag, TObjectPtr<USOCAIBehavior>> ChildBehaviorMap;
#pragma endregion

#pragma region Behavior

public:

	//CalculateCurrentAction: Decide the action that this actor should be engaging in at this time
	//InActor is the actor we are deciding the action for (an AIController/Character)
	//OutAction is the action that we have decided on
	//BehaviorPath is the path of behaviors that we have taken to get to this point
	//InParentAction is the action that the parent behavior has decided on, used to override behaviors of children
	virtual bool CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction = FSOCAIAction()) const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName="CalculateCurrentAction", Category = "AI|Behavior")
	bool K2_CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction = FSOCAIAction()) const;
	
	UFUNCTION(BlueprintPure, Category = "AI|Director")
	AActor* GetDirector(const AActor* InBehaviorActor) const;
	
	virtual void OnEnteredBehavior(AActor* InBehaviorActor, const FSOCAIAction& InEnteredBehaviorAction, const FSOCAIAction& InExitedBehaviorAction) const;

	virtual void OnExitedBehavior(AActor* InBehaviorActor, const FSOCAIAction& InExitedBehaviorAction, const FSOCAIAction& InEnteredBehaviorAction) const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnEnteredBehavior", Category = "AI|Behavior")
	void K2_OnEnteredBehavior(const AActor* InBehaviorActor, const FSOCAIAction& InEnteredBehaviorAction, const FSOCAIAction& InExitedBehaviorAction) const;

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnExitedBehavior", Category = "AI|Behavior")
	void K2_OnExitedBehavior(const AActor* InBehaviorActor, const FSOCAIAction& InExitedBehaviorAction, const FSOCAIAction& InEnteredBehaviorAction) const;

#pragma endregion

#pragma region Gameplay Ability System

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	TArray<FBehaviorGameplayAbility> BehaviorGameplayAbilities;

#pragma endregion

};
