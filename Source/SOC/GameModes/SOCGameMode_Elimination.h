
#pragma once

#include "CoreMinimal.h"
#include "SOCGameModeBase.h"
#include "SOCGameMode_Elimination.generated.h"

class UObjectiveInfoCollection;
/**
 * 
 */
UCLASS()
class SOC_API ASOCGameMode_Elimination : public ASOCGameModeBase
{
	GENERATED_BODY()

#pragma region Framework
protected:
	ASOCGameMode_Elimination();
	
#pragma endregion


#pragma region Objectives

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	TArray<UObjectiveInfoCollection*> PreMatchObjectiveCollections;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	TArray<UObjectiveInfoCollection*> MatchObjectiveCollections;

#pragma endregion 

#pragma region Player

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	
#pragma endregion 


#pragma region Match State
	
	/** Overridable virtual function to dispatch the appropriate transition functions before GameState and Blueprints get SetMatchState calls. */
	virtual void OnMatchStateSet() override;
	
	/** Called when the state transitions to InProgress */
	virtual void HandleMatchHasStarted() override;
	

#pragma endregion

};
