// Copyright Epic Games, Inc. All Rights Reserved.


#include "SOCGameModeBase.h"

#pragma region Framework

ASOCGameModeBase::ASOCGameModeBase()
{
	bDelayedStart = true;
}

#pragma endregion

#pragma region Restart Player
	
bool ASOCGameModeBase::PlayerCanRestart_Implementation(APlayerController* Player)
{
	if (!IsMatchInProgress() && !IsMatchWaitingToStart())
	{
		return false;
	}

	return true;
}

void ASOCGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	// If players should start as spectators, leave them in the spectator state
	if (!bStartPlayersAsSpectators && !MustSpectate(NewPlayer))
	{
		// If match is in progress, start the player
		if (PlayerCanRestart(NewPlayer))
		{
			RestartPlayer(NewPlayer);
		}
		// Check to see if we should start right away, avoids a one frame lag in single player games
		else if (GetMatchState() == MatchState::WaitingToStart)
		{
			// Check to see if we should start the match
			if (ReadyToStartMatch())
			{
				StartMatch();
			}
		}
	}
}


#pragma endregion

#pragma region Match State

/** Returns true if the match state is WaitingToStart */
bool ASOCGameModeBase::IsMatchWaitingToStart() const
{
	if (GetMatchState() == MatchState::WaitingToStart)
	{
		return true;
	}

	return false;
}

/** Called when the state transitions to WaitingToStart */
void ASOCGameModeBase::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();

	// start human players, because we allow them to run around before the match starts
	for( FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator )
	{
		APlayerController* PlayerController = Iterator->Get();
		if (PlayerController && (PlayerController->GetPawn() == nullptr) && PlayerCanRestart(PlayerController))
		{
			RestartPlayer(PlayerController);
		}
	}
}

/** Overridable virtual function to dispatch the appropriate transition functions before GameState and Blueprints get SetMatchState calls. */
void ASOCGameModeBase::OnMatchStateSet()
{
	Super::OnMatchStateSet();
}
#pragma endregion