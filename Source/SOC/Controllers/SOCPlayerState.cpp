// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCPlayerState.h"
#include "ObjectiveSystem/Components/ObjectiveTrackerComponent.h"

ASOCPlayerState::ASOCPlayerState()
{
	ObjectiveTrackerComponent = CreateDefaultSubobject<UObjectiveTrackerComponent>(TEXT("ObjectiveTrackerComponent"));
}


