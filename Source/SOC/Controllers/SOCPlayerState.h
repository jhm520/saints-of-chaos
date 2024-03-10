// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SOCPlayerState.generated.h"

class UObjectiveTrackerComponent;
/**
 * 
 */
UCLASS()
class SOC_API ASOCPlayerState : public APlayerState
{
	GENERATED_BODY()
#pragma region Framework
	ASOCPlayerState();
#pragma endregion

#pragma region Objective System
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	UObjectiveTrackerComponent* ObjectiveTrackerComponent;
#pragma endregion
};
