// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCGameState.h"
#include "ObjectiveSystem/Components/ObjectiveTrackerComponent.h"

#pragma region Framework

ASOCGameState::ASOCGameState()
{
	ObjectiveTrackerComponent = CreateDefaultSubobject<UObjectiveTrackerComponent>(TEXT("ObjectiveTrackerComponent"));
}

#pragma endregion

#pragma region Objectives

UObjectiveTrackerComponent* ASOCGameState::GetObjectiveTrackerComponent() const
{
	return ObjectiveTrackerComponent;
}

#pragma endregion