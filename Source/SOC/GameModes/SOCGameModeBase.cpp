// Copyright Epic Games, Inc. All Rights Reserved.


#include "SOCGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "SOC/Controllers/SOCAIPlayerController.h"
#include "SOC/Gameplay/PlayerStart/SOCPlayerStartBase.h"

#pragma region Framework

ASOCGameModeBase::ASOCGameModeBase()
{
	bDelayedStart = true;
}

void ASOCGameModeBase::BeginPlay()
{
	Super::BeginPlay();
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

	HandleStartingSoloPlay();
}

/** Overridable virtual function to dispatch the appropriate transition functions before GameState and Blueprints get SetMatchState calls. */
void ASOCGameModeBase::OnMatchStateSet()
{
	Super::OnMatchStateSet();
}
#pragma endregion

#pragma region Character Death

void ASOCGameModeBase::OnActorKilled(AActor* Victim, AActor* Attacker, AController* ControllerInstigator)
{
	
}

#pragma endregion

#pragma region Character Death

void ASOCGameModeBase::HandleStartingSoloPlay()
{
	ENetMode NetMode = GetNetMode();

	if (NetMode != NM_Standalone)
	{
		return;
	}
	
	//add AI players
	for (int32 i = 0; i < NumStandaloneAIPlayers; i++)
	{
		ASOCAIPlayerController* NewAIPC = GetWorld()->SpawnActor<ASOCAIPlayerController>(AIPlayerControllerClass);

		if (NewAIPC)
		{
			HandleStartingNewAIPlayer(NewAIPC);
		}
	}
}

void ASOCGameModeBase::HandleStartingNewAIPlayer(AController* NewPlayer)
{
	//spawn an AI player
	RestartPlayer(NewPlayer);
}


UClass* ASOCGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<ASOCAIPlayerController>())
	{
		return AIPlayerPawnClass;
	}
	
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}


#pragma endregion