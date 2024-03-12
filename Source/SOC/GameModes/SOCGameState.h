// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ObjectiveSystem/Interfaces/ObjectiveTrackerInterface.h"
#include "SOCGameState.generated.h"

class UObjectiveTrackerComponent;
/**
 * 
 */
UCLASS()
class SOC_API ASOCGameState : public AGameState, public IObjectiveTrackerInterface
{
	GENERATED_BODY()

#pragma region Framework
protected:
	ASOCGameState();
#pragma endregion

#pragma region Objectives

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	UObjectiveTrackerComponent* ObjectiveTrackerComponent;
	
	virtual UObjectiveTrackerComponent* GetObjectiveTrackerComponent() const override;

#pragma endregion

};
