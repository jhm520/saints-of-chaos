
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SOCGameModeBase.h"
#include "SOCGameMode_Elimination.generated.h"

class UObjectiveInfoCollection;
class ASOCBuilding;
class AObjective;
class AObjectiveGroup;
class AActorSpawner;
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

	virtual void ResetLevel() override;
	
#pragma endregion


#pragma region Objectives

	//pre match
	virtual void SetupPreMatchObjectives();
	virtual void BeginPreMatchObjectives();

	//match
	virtual void SetupMatchObjectives();
	virtual void BeginMatchObjectives();

	//post match
	virtual void SetupPostMatchObjectives();
	virtual void BeginPostMatchObjectives();

	/** Called when the state transitions to WaitingToStart */
	virtual void HandleMatchIsWaitingToStart_Objectives();

	/** Called when the state transitions to InProgress */
	virtual void HandleMatchHasStarted_Objectives();

	/** Called when the state transitions to WaitingPostMatch */
	virtual void HandleMatchHasEnded_Objectives();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	TArray<UObjectiveInfoCollection*> PreMatchObjectiveCollections;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	TArray<UObjectiveInfoCollection*> PreMatchPlayerObjectiveCollections;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	TArray<UObjectiveInfoCollection*> MatchObjectiveCollections;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	TArray<UObjectiveInfoCollection*> MatchPlayerObjectiveCollections;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	TArray<UObjectiveInfoCollection*> PostMatchObjectiveCollections;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	TArray<UObjectiveInfoCollection*> PostMatchPlayerObjectiveCollections;
	

#pragma endregion 

#pragma region Player

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	
#pragma endregion

#pragma region AI Player

	virtual void HandleStartingNewAIPlayer(AController* NewPlayer) override;
	
#pragma endregion 


#pragma region Match State
	
	/** Overridable virtual function to dispatch the appropriate transition functions before GameState and Blueprints get SetMatchState calls. */
	virtual void OnMatchStateSet() override;

	/** Called when the state transitions to WaitingToStart */
	virtual void HandleMatchIsWaitingToStart() override;
	
	/** Called when the state transitions to InProgress */
	virtual void HandleMatchHasStarted() override;
	
	/** Called when the map transitions to WaitingPostMatch */
	virtual void HandleMatchHasEnded() override;
	
#pragma endregion
	
#pragma region Ready Check

	virtual void SetupReadyCheckObjectives();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	FGameplayTagContainer AllPlayersReadyCheckObjectiveTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	FGameplayTagContainer PlayerReadyCheckObjectiveTags;
	
	UPROPERTY()
	TObjectPtr<AObjectiveGroup> AllPlayersReadyObjectiveGroup;
	
	UFUNCTION()
	void OnReadyCheckObjectiveComplete(AObjectiveGroup* ObjectiveGroup, AObjective* Objective, AActor* Assignee, AActor* InInstigator);

	UFUNCTION()
	void OnReadyCheckObjectiveFailed(AObjectiveGroup* ObjectiveGroup, AObjective* Objective, AActor* Assignee, AActor* InInstigator);
	
	UFUNCTION()
	void OnAllPlayersReadyCheckObjectiveComplete(AObjective* Objective, AActor* Assignee, AActor* InInstigator);

	UFUNCTION()
	void OnAllPlayersReadyCheckObjectiveFailed(AObjective* Objective, AActor* Assignee, AActor* InInstigator);

	UPROPERTY()
	FTimerHandle TimerHandle_StartMatch;
	
	UFUNCTION()
	void Timer_StartMatch();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	float StartMatchTimerDuration;
	
#pragma endregion

	
#pragma region Rematch

	virtual void SetupRematchObjectives();

	UPROPERTY()
	TObjectPtr<AObjectiveGroup> AllPlayersRematchObjectiveGroup;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	FGameplayTagContainer AllPlayersRematchObjectiveTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	FGameplayTagContainer PlayerRematchObjectiveTags;
	
	UFUNCTION()
	void OnRematchObjectiveComplete(AObjective* Objective, AActor* Assignee, AActor* InInstigator);

	UFUNCTION()
	void OnRematchObjectiveFailure(AObjective* Objective, AActor* Assignee, AActor* InInstigator);
	
	UFUNCTION()
	void OnAllPlayersRematchObjectiveComplete(AObjective* Objective, AActor* Assignee, AActor* InInstigator);

	UFUNCTION()
	void OnAllPlayersRematchObjectiveFailed(AObjective* Objective, AActor* Assignee, AActor* InInstigator);

	UFUNCTION()
	void OnRematchObjectiveBegin(AObjective* Objective, AActor* Assignee);
	
	UPROPERTY()
	FTimerHandle TimerHandle_Rematch;
	
	UFUNCTION()
	void Timer_Rematch();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	float RematchTimerDuration;

	UFUNCTION()
	virtual void Rematch();
	
#pragma endregion

#pragma region Exit Match

	UFUNCTION()
	virtual void ExitMatch();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	FName ExitMatchLevelName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	TSubclassOf<AGameModeBase> ExitMatchGameMode;
	
#pragma endregion

#pragma region Buildings

	void SetupMatchBuildingsForAllPlayers();

	void SetupMatchBuildingsForPlayer(AController* Controller);

	void SetupDestroyEnemyBuildingsObjectives();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buildings")
	TSubclassOf<AActor> BuildingSpawnerClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buildings")
	FGameplayTagContainer DestroyBuildingsObjectiveTags;

	UPROPERTY(Transient)
	TObjectPtr<AObjective> DestroyEnemyBuildingsObjective;

	void OnBuildingDestroyed(ASOCBuilding* BuildingVictim, AActor* Attacker, AController* ControllerInstigator);

	UFUNCTION()
	void OnDestroyEnemyBuildingsObjectiveComplete(AObjective* Objective, AActor* Assignee, AActor* InInstigator);
#pragma endregion

#pragma region Actor Death

	virtual void OnActorKilled(AActor* Victim, AActor* Attacker, AController* ControllerInstigator) override;

#pragma endregion


};
