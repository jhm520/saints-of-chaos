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
protected:
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

	/** Overridable virtual function to dispatch the appropriate transition functions before GameState and Blueprints get SetMatchState calls. */
	virtual void OnMatchStateSet() override;
#pragma endregion

#pragma region Actor Death
public:
	virtual void OnActorKilled(AActor* Victim, AActor* Attacker, AController* ControllerInstigator);

#pragma endregion

#pragma region Solo Play Mode
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Solo Play")
	int32 NumStandaloneAIPlayers = 1;

	void HandleStartingSoloPlay();

	virtual void HandleStartingNewAIPlayer(AController* NewPlayer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Solo Play")
	TSubclassOf<APawn> AIPlayerPawnClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Solo Play")
	TSubclassOf<AController> AIPlayerControllerClass;

	/** Returns default pawn class for given controller */
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

#pragma endregion

};
