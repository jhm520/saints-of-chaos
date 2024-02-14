// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreUtilityBlueprintLibrary.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

int32 UCoreUtilityBlueprintLibrary::GetAuthPlayerControllerId(const UObject* WorldContextObject, APlayerController* PlayerController)
{
	if (!WorldContextObject || !WorldContextObject->GetWorld())
	{
		return -1;
	}

	if (!PlayerController)
	{
		return -1;
	}

	if (!PlayerController->HasAuthority())
	{
		return -1;
	}

	AGameStateBase* GameStateBase = WorldContextObject->GetWorld()->GetGameState<AGameStateBase>();

	if (!GameStateBase)
	{
		return -1;
	}

	TArray<APlayerState*> PlayerStates = GameStateBase->PlayerArray;

	APlayerState* OwningPlayerState = PlayerController->GetPlayerState<APlayerState>();

	if (!OwningPlayerState)
	{
		return -1;
	}

	int32 PlayerIndex;
	
	bool bFoundPlayer = PlayerStates.Find(OwningPlayerState, PlayerIndex);

	if (!bFoundPlayer)
	{
		return -1;
	}

	return PlayerIndex;
}
