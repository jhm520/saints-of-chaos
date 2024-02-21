// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOCAI/Behavior/SOCAIBehavior.h"
#include "SOCAIBehavior_Attack.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API USOCAIBehavior_Attack : public USOCAIBehavior
{
	GENERATED_BODY()
	
#pragma region Behavior

public:
	USOCAIBehavior_Attack();

	//CalculateCurrentAction: Decide the action that this actor should be engaging in at this time
	//InActor is the actor we are deciding the action for (an AIController/Character)
	//OutAction is the action that we have decided on
	//BehaviorPath is the path of behaviors that we have taken to get to this point
	//InParentAction is the action that the parent behavior has decided on, used to override behaviors of children
	virtual bool CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction = FSOCAIAction()) const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Behavior")
	float DistanceThreshold;

#pragma endregion
};
