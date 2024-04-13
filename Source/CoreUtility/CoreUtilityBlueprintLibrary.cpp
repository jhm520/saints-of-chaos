// © 2024 John Henry Miller. All rights reserved

#include "CoreUtilityBlueprintLibrary.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
UE_DISABLE_OPTIMIZATION
int32 UCoreUtilityBlueprintLibrary::GetAuthPlayerControllerId(const UObject* WorldContextObject, AController* PlayerController)
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
UE_ENABLE_OPTIMIZATION