// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SOCAIDataAsset.h"
#include "SOCAIGameplayTags.h"
#include "SOCAIController.generated.h"

/**
 * 
 */
class USOCAIBehavior;
class USOCAIDataAsset;
class ASOCAIBehaviorManager;

UCLASS(Blueprintable)
class SOCAI_API ASOCAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASOCAIController(const FObjectInitializer& ObjectInitializer);


protected:

	UPROPERTY(Transient)
	FGameplayTag CurrentBehaviorState = FGameplayTag::EmptyTag;

	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TObjectPtr<ASOCAIBehaviorManager> BehaviorManager = nullptr;

public:
	
	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	ASOCAIBehaviorManager* GetBehaviorManager(){return BehaviorManager;};

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
	UFUNCTION(BlueprintCallable, Category = "AI|Behavior")
	bool SetBehaviorState(const FGameplayTag& InBehaviorTag);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	TSubclassOf<ASOCAIBehaviorManager> BehaviorManagerClass;

	UFUNCTION()
	bool TryCreateBehaviorManager();
	
};
