// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "SOCAIDataAsset.generated.h"

/**
 * 
 */
class USOCAIBehavior;

UCLASS()
class SOCAI_API USOCAIDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	TMap<FGameplayTag, TSubclassOf<USOCAIBehavior>> BehaviorClassMap;
};
