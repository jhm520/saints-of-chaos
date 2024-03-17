// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCGameState.h"
#include "ObjectiveSystem/Components/ObjectiveTrackerComponent.h"
#include "SOC/Engine/SOCGameInstance.h"

#pragma region Framework

ASOCGameState::ASOCGameState()
{
	ObjectiveTrackerComponent = CreateDefaultSubobject<UObjectiveTrackerComponent>(TEXT("ObjectiveTrackerComponent"));
}

void ASOCGameState::BeginPlay()
{
	Super::BeginPlay();
	
	USOCGameInstance* GameInstance = GetWorld()->GetGameInstance<USOCGameInstance>();

	if (GameInstance)
	{
		GameInstance->OnGameStateHasBegunPlay(this);
	}
	
}

/** Match state has changed */
void ASOCGameState::OnRep_MatchState()
{
	Super::OnRep_MatchState();

	GameStateMatchStateSetEvent.Broadcast(MatchState);
}
UE_DISABLE_OPTIMIZATION
void ASOCGameState::OnRep_ReplicatedHasBegunPlay()
{
	Super::OnRep_ReplicatedHasBegunPlay();
}
UE_ENABLE_OPTIMIZATION

#pragma endregion

#pragma region Objectives

UObjectiveTrackerComponent* ASOCGameState::GetObjectiveTrackerComponent() const
{
	return ObjectiveTrackerComponent;
}

#pragma endregion