// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SOCAI/Data/SOCAIDataAsset.h"
#include "../SOCAIGameplayTags.h"
#include "SOCAI/Behavior/SOCAIBehavior.h"
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
	FGameplayTag CurrentBehaviorState = SOCAIBehaviorTags::Behavior;

	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TObjectPtr<ASOCAIBehaviorManager> BehaviorManager = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TObjectPtr<USOCAIBehavior> CurrentBehavior = nullptr;

	virtual void TickUpdateBehavior(const float DeltaSeconds);

	UFUNCTION(BlueprintNativeEvent, Category = "AI|Behavior")
	void DoAction(const FSOCAIAction& InAction);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	FGameplayTag RootBehaviorState = SOCAIBehaviorTags::Behavior;
	
public:
	
	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	ASOCAIBehaviorManager* GetBehaviorManager(){return BehaviorManager;};

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(const float DeltaSeconds) override;

	
	UFUNCTION(BlueprintCallable, Category = "AI|Behavior")
	bool SetBehaviorState(const FGameplayTag& InBehaviorTag);

	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const FGameplayTag& GetCurrentBehaviorState() {return CurrentBehaviorState;};

	UFUNCTION(BlueprintCallable, Category = "AI|Behavior")
	USOCAIBehavior* GetBehavior(const FGameplayTag& InBehaviorTag);

	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const USOCAIBehavior* GetCurrentBehavior(){return CurrentBehavior;};

	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const FGameplayTag& GetRootBehaviorState(){return RootBehaviorState;};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	TSubclassOf<ASOCAIBehaviorManager> BehaviorManagerClass;

	UFUNCTION()
	bool TryCreateBehaviorManager();
	
};
