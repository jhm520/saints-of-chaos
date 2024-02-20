// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "GameplayTagContainer.h"
#include "SOCAIBehaviorManager.generated.h"

/** TODO: Change this to a data asset, USOCAIBehaviorTree
 * 
 */
class USOCAIDataAsset;
class USOCAIBehavior;
UCLASS(Blueprintable)
class SOCAI_API ASOCAIBehaviorManager : public AInfo
{
	GENERATED_BODY()
#pragma region Framework
public:
	
	ASOCAIBehaviorManager(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
#pragma endregion

#pragma region Behavior
public:
	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	USOCAIBehavior* GetBehavior(const FGameplayTag& InBehaviorTag);
	
	void SetupBehaviorTree();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	TObjectPtr<USOCAIDataAsset> SOCAIDataAsset;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TMap<FGameplayTag, TObjectPtr<USOCAIBehavior>> BehaviorMap;

#pragma endregion

};
