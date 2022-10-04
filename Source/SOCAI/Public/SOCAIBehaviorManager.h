// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "GameplayTagContainer.h"
#include "SOCAIBehaviorManager.generated.h"

/**
 * 
 */
class USOCAIDataAsset;
class USOCAIBehavior;
UCLASS(Blueprintable)
class SOCAI_API ASOCAIBehaviorManager : public AInfo
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	TArray<TSubclassOf<USOCAIBehavior>> BehaviorClassArray;

	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TMap<FGameplayTag, TObjectPtr<USOCAIBehavior>> BehaviorMap;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
};
