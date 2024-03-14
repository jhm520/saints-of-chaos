// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCPlayerState.h"

#include "ObjectiveSystem/Components/ObjectiveAssigneeComponent.h"
#include "ObjectiveSystem/Components/ObjectiveTrackerComponent.h"

ASOCPlayerState::ASOCPlayerState()
{
	ObjectiveAssigneeComponent = CreateDefaultSubobject<UObjectiveAssigneeComponent>(TEXT("ObjectiveAssigneeComponent"));
}


