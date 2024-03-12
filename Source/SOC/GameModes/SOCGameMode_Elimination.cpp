//


#include "SOCGameMode_Elimination.h"

#include "SOCGameState.h"
#include "ObjectiveSystem/ObjectiveSystemBlueprintLibrary.h"
#include "ObjectiveSystem/DataAssets/ObjectiveInfoCollection.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

#pragma region Framework

ASOCGameMode_Elimination::ASOCGameMode_Elimination()
{
	bDelayedStart = true;
}

#pragma endregion

#pragma region Player

void ASOCGameMode_Elimination::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	if (!NewPlayer)
	{
		return;
	}

	APlayerState* PlayerState = NewPlayer->PlayerState;

	if (!PlayerState)
	{
		return;
	}

	TArray<AActor*> Assignees;
	Assignees.Add(PlayerState);

	if (GetMatchState() == MatchState::WaitingToStart)
	{
		for (UObjectiveInfoCollection* Collection : PreMatchObjectiveCollections)
		{
			UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByCollection(GameState, Collection, Assignees);
		}
	}
	else if (GetMatchState() == MatchState::InProgress)
	{
		for (UObjectiveInfoCollection* Collection : MatchObjectiveCollections)
		{
			UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByCollection(GameState, Collection, Assignees);
		}
	}
}
	
#pragma endregion 

#pragma region Match State
	
/** Overridable virtual function to dispatch the appropriate transition functions before GameState and Blueprints get SetMatchState calls. */
void ASOCGameMode_Elimination::OnMatchStateSet()
{
	Super::OnMatchStateSet();
	
	
}

/** Called when the state transitions to InProgress */
void ASOCGameMode_Elimination::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
	
	if (!GameState)
	{
		return;
	}

	for (UObjectiveInfoCollection* Collection : MatchObjectiveCollections)
	{
		UObjectiveSystemBlueprintLibrary::BeginObjectivesForActorByCollection(GameState, Collection);
	}
}
#pragma endregion