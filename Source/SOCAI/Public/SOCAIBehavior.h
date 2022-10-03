// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SOCAIGameplayTags.h"
#include "SOCAIBehavior.generated.h"

/**
 * 
 */
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

public:

	USOCAIBehavior(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const FGameplayTag& GetBehaviorTag(){return BehaviorTag;};
	
	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const FGameplayTag& GetParentBehaviorTag(){return ParentBehaviorTag;};

	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const FGameplayTagContainer& GetChildBehaviorTags(){return ChildBehaviorTags;};

	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TObjectPtr<USOCAIBehavior> ParentBehavior;

	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TSet<TObjectPtr<USOCAIBehavior>> ChildBehaviorSet;
	
};
