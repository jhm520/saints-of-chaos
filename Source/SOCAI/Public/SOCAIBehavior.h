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

public:

	USOCAIBehavior(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	FGameplayTag MainBehaviorTag;
	
	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	FGameplayTagContainer BehaviorTags;

	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TSet<TObjectPtr<USOCAIBehavior>> BehaviorSet;
	
};
