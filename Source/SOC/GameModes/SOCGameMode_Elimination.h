
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SOCGameModeBase.h"
#include "SOCGameMode_Elimination.generated.h"

class UObjectiveInfoCollection;
class ASOCBuilding;
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
	
	/** Called when the map transitions to WaitingPostMatch */
	virtual void HandleMatchHasEnded() override;
	
#pragma endregion

#pragma region Buildings
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	FGameplayTagContainer DestroyBuildingsObjectiveTags;

	void OnBuildingDestroyed(ASOCBuilding* BuildingVictim, AActor* Attacker, AController* ControllerInstigator);

	UFUNCTION()
	void OnDestroyEnemyBuildingsObjectiveComplete(AObjective* Objective, AActor* Assignee, AActor* InInstigator);
#pragma endregion

#pragma region Actor Death

	virtual void OnActorKilled(AActor* Victim, AActor* Attacker, AController* ControllerInstigator) override;

#pragma endregion


};
