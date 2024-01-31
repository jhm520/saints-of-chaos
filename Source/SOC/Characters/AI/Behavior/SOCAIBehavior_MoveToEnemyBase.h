// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOCAI/Behavior/SOCAIBehavior.h"
#include "SOCAIBehavior_MoveToEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API USOCAIBehavior_MoveToEnemyBase : public USOCAIBehavior
{
	GENERATED_BODY()

#pragma region Behavior

	virtual bool CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction = FSOCAIAction()) const override;
	
#pragma endregion

#pragma region Enemy Base
protected:
	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	bool GetEnemyBaseLocation(const AActor* InActor, FVector& OutEnemyBaseLocation) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Behavior")
	float DistanceThreshold = 200.0f;
	
#pragma endregion

};
