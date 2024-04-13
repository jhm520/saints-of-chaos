// © 2024 John Henry Miller. All rights reserved
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
	
#pragma region Framework
protected:
	USOCAIBehavior_MoveToEnemyBase();
#pragma endregion

#pragma region Behavior

	virtual bool CalculateCurrentAction(const AActor* InActor, FSOCAIAction& OutAction, UPARAM(ref) FGameplayTagContainer& BehaviorPath, const FSOCAIAction& InParentAction = FSOCAIAction()) const override;
	
#pragma endregion

#pragma region Enemy Base
protected:
	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	bool GetEnemyBaseLocation(const AActor* InActor, FVector& OutEnemyBaseLocation) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Behavior")
	float DistanceThreshold;
	
#pragma endregion

};
