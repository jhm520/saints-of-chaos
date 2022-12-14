// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../SOCAIGameplayTags.h"
#include "SOCAIBehavior.generated.h"

//struct to represent an AIController's current action
USTRUCT(BlueprintType)
struct SOCAI_API FSOCAIAction
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	FGameplayTag ActionTag = SOCAIActionTags::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	FGameplayTag BehaviorTag = SOCAIBehaviorTags::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Behavior")
	FVector TargetLocation{ForceInit};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Behavior")
	TObjectPtr<AActor> TargetActor = nullptr;

	FSOCAIAction(){}
};

/**
 * 
 */
class ASOCAIController;
UCLASS(Blueprintable, Abstract)
class SOCAI_API USOCAIBehavior : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	FGameplayTag ParentBehaviorTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	FGameplayTag BehaviorTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	FGameplayTagContainer ChildBehaviorTags;

	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TObjectPtr<USOCAIBehavior> ParentBehavior = nullptr;;
	
	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TMap<FGameplayTag, TObjectPtr<USOCAIBehavior>> ChildBehaviorMap;

public:

	//Decide the action that this controller should be engaging in at this time
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "AI|Behavior")
	bool CalculateCurrentControllerAction(const ASOCAIController* InController, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction = FSOCAIAction()) const;

	UFUNCTION()
	void SetParentBehavior(USOCAIBehavior* InParentBehavior){ParentBehavior = InParentBehavior;};

	UFUNCTION()
	void AddChildBehavior(USOCAIBehavior* InChildBehavior);

	UFUNCTION()
	USOCAIBehavior* GetChildBehavior(const FGameplayTag& InBehaviorTag) const;

	USOCAIBehavior(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const FGameplayTag& GetBehaviorTag() const {return BehaviorTag;};
	
	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const FGameplayTag& GetParentBehaviorTag() const {return ParentBehaviorTag;};

	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const FGameplayTagContainer& GetChildBehaviorTags() const{return ChildBehaviorTags;};
	
};
