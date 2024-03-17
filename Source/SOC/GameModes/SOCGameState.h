// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ObjectiveSystem/Interfaces/ObjectiveTrackerInterface.h"
#include "SOCGameState.generated.h"

class UObjectiveTrackerComponent;

/**
	 * Match state has changed via SetMatchState()
	 *
	 * @param MatchState new match state
	 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameStateMatchStateSetEvent, FName /*MatchState*/, MatchState);


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

	virtual void BeginPlay() override;
	
	/** Match state has changed */
	virtual void OnRep_MatchState() override;

	virtual void OnRep_ReplicatedHasBegunPlay() override;
#pragma endregion
	
	UPROPERTY(BlueprintAssignable, Category = "Game State")
	FGameStateMatchStateSetEvent GameStateMatchStateSetEvent;
	
#pragma region Objectives

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	UObjectiveTrackerComponent* ObjectiveTrackerComponent;
	
	virtual UObjectiveTrackerComponent* GetObjectiveTrackerComponent() const override;

#pragma endregion

};
