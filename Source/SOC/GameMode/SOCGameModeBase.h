// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CoreUtility/GameMode/CoreGameModeBase.h"
#include "SOCGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API ASOCGameModeBase : public ACoreGameModeBase
{
	GENERATED_BODY()

#pragma region Framework
	ASOCGameModeBase();
#pragma endregion

#pragma region Restart Player
	
	virtual bool PlayerCanRestart_Implementation(APlayerController* Player) override;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

#pragma endregion
	
#pragma region Match State

	/** Returns true if the match state is WaitingToStart */
	UFUNCTION(BlueprintCallable, Category="Game")
	virtual bool IsMatchWaitingToStart() const;

	/** Called when the state transitions to WaitingToStart */
	virtual void HandleMatchIsWaitingToStart() override;
#pragma endregion

};
