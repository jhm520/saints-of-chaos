// © 2024 John Henry Miller. All rights reserved
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

	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	TArray<TSubclassOf<USOCAIBehavior>> BehaviorClasses;

public:
	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	TArray<TSubclassOf<USOCAIBehavior>> GetBehaviorClasses() const {return BehaviorClasses;};

};
