// © 2024 John Henry Miller. All rights reserved

#include "CoreGameModeBase.h"
#include "EngineUtils.h"
#include "CoreUtility/PlayerStart/Interfaces/PlayerStartInterface.h"
#include "Engine/PlayerStartPIE.h"
#include "GameFramework/PlayerStart.h"
#include "Interfaces/CoreGameModeActorInterface.h"

#pragma region Reset

bool ACoreGameModeBase::ShouldReset_Implementation(AActor* ActorToReset)
{
	ICoreGameModeActorInterface* CoreGameModeActorInterface = Cast<ICoreGameModeActorInterface>(ActorToReset);

	if (CoreGameModeActorInterface)
	{
		return CoreGameModeActorInterface->ShouldReset(ActorToReset);
	}

	return Super::ShouldReset_Implementation(ActorToReset);
}
#pragma endregion

#pragma region Player Start

AActor* ACoreGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	APlayerController* PlayerController = Cast<APlayerController>(Player);

	if (!PlayerController)
	{
		return Super::ChoosePlayerStart_Implementation(Player);
	}
	
	// Choose a player start
	UWorld* World = GetWorld();

	if (!World)
	{
		return nullptr;
	}
	
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		APlayerStart* PlayerStart = *It;

		if (!PlayerStart)
		{
			continue;
		}

		IPlayerStartInterface* PlayerStartInterface = Cast<IPlayerStartInterface>(PlayerStart);

		if (!PlayerStartInterface)
		{
			continue;
		}

		if (PlayerStartInterface->CanPlayerSpawnAt(PlayerController))
		{
			return PlayerStart;
		}
	}

	return Super::ChoosePlayerStart_Implementation(Player);
}

#pragma endregion