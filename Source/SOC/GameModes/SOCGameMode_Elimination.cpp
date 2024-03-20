//


#include "SOCGameMode_Elimination.h"

#include "SOCGameState.h"
#include "ObjectiveSystem/ObjectiveSystemBlueprintLibrary.h"
#include "ObjectiveSystem/DataAssets/ObjectiveInfoCollection.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "ObjectiveSystem/Actors/Objective.h"
#include "SOC/Gameplay/Buildings/Building.h"
#include "SOC/Gameplay/Buildings/BuildingSubsystem.h"
#include "ObjectiveSystem/Actors/ObjectiveGroup.h"

#pragma region Framework

ASOCGameMode_Elimination::ASOCGameMode_Elimination()
{
	bDelayedStart = true;
	StartMatchTimerDuration = 5.0f;
	RematchTimerDuration = 15.0f;
}

#pragma endregion

#pragma region Player

void ASOCGameMode_Elimination::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	if (!NewPlayer)
	{
		return;
	}

	APlayerState* PlayerState = NewPlayer->PlayerState;

	if (!PlayerState)
	{
		return;
	}

	TArray<AActor*> Assignees;
	Assignees.Add(PlayerState);

	if (GetMatchState() == MatchState::WaitingToStart)
	{
		//set up and begin any pre-match objectives
		for (UObjectiveInfoCollection* Collection : PreMatchObjectiveCollections)
		{
			TArray<AObjective*> PreMatchObjectives;
			UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByCollection(GameState, Collection, Assignees, PreMatchObjectives);
			UObjectiveSystemBlueprintLibrary::BeginObjectivesForActorByCollection(GameState, Collection);
		}

		//set up and begin any pre-match objectives
		for (UObjectiveInfoCollection* Collection : PreMatchPlayerObjectiveCollections)
		{
			TArray<AObjective*> PreMatchPlayerObjectives;

			UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByCollection(PlayerState, Collection, Assignees, PreMatchPlayerObjectives);
			UObjectiveSystemBlueprintLibrary::BeginObjectivesForActorByCollection(PlayerState, Collection);
		}

		//set up post match objectives
		for (UObjectiveInfoCollection* Collection : PostMatchObjectiveCollections)
		{
			TArray<AObjective*> PostMatchObjectives;
			UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByCollection(GameState, Collection, Assignees,PostMatchObjectives);
		}

		for (UObjectiveInfoCollection* Collection : PostMatchPlayerObjectiveCollections)
		{
			TArray<AObjective*> PostMatchPlayerObjectives;
			UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByCollection(PlayerState, Collection, Assignees, PostMatchPlayerObjectives);
		}
		
		SetupReadyCheckObjectives();

		SetupRematchObjectives();

		//set up the objectives for the match
		for (UObjectiveInfoCollection* Collection : MatchObjectiveCollections)
		{
			TArray<AObjective*> MatchObjectives;
			UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByCollection(GameState, Collection, Assignees, MatchObjectives);
		}
		
	}
	else if (GetMatchState() == MatchState::InProgress)
	{
		for (UObjectiveInfoCollection* Collection : MatchObjectiveCollections)
		{
			TArray<AObjective*> MatchObjectives;
			UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByCollection(GameState, Collection, Assignees, MatchObjectives);
			UObjectiveSystemBlueprintLibrary::BeginObjectivesForActorByCollection(GameState, Collection);
		}
	}
}
	
#pragma endregion 

#pragma region Match State
	
/** Overridable virtual function to dispatch the appropriate transition functions before GameState and Blueprints get SetMatchState calls. */
void ASOCGameMode_Elimination::OnMatchStateSet()
{
	Super::OnMatchStateSet();
	
	
}

/** Called when the state transitions to InProgress */
void ASOCGameMode_Elimination::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
	
	if (!GameState)
	{
		return;
	}
	
	TArray<AActor*> Assignees;

	for (APlayerState* Player : GameState->PlayerArray)
	{
		Assignees.Add(Player);
	}

	for (UObjectiveInfoCollection* Collection : MatchObjectiveCollections)
	{
		TArray<AObjective*> MatchObjectives;
		UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByCollection(GameState, Collection, Assignees, MatchObjectives);
		UObjectiveSystemBlueprintLibrary::BeginObjectivesForActorByCollection(GameState, Collection);
	}

	TArray<AObjective*> DestroyEnemyBuildingsObjectives;
	UObjectiveSystemBlueprintLibrary::GetObjectivesByTags(this, DestroyBuildingsObjectiveTags, DestroyEnemyBuildingsObjectives);

	for (AObjective* Objective : DestroyEnemyBuildingsObjectives)
	{
		Objective->OnObjectiveComplete.AddDynamic(this, &ASOCGameMode_Elimination::OnDestroyEnemyBuildingsObjectiveComplete);
	}
}

/** Called when the map transitions to WaitingPostMatch */
void ASOCGameMode_Elimination::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Match Has Ended");
	
	if (!GameState)
	{
		return;
	}
	
	TArray<AActor*> Assignees;

	for (APlayerState* Player : GameState->PlayerArray)
	{
		Assignees.Add(Player);
	}

	//begin any post match objectives
	for (UObjectiveInfoCollection* Collection : PostMatchObjectiveCollections)
	{
		UObjectiveSystemBlueprintLibrary::BeginObjectivesForActorByCollection(GameState, Collection);
	}

	//begin any post match objectives for each player
	for (APlayerState* Player : GameState->PlayerArray)
	{
		for (UObjectiveInfoCollection* Collection : PostMatchPlayerObjectiveCollections)
		{
			UObjectiveSystemBlueprintLibrary::BeginObjectivesForActorByCollection(Player, Collection);
		}
	}
	
	//set the rematch timer
	GetWorldTimerManager().SetTimer(TimerHandle_Rematch, this, &ASOCGameMode_Elimination::Timer_Rematch, RematchTimerDuration, false);
}
#pragma endregion

#pragma region Ready Check

void ASOCGameMode_Elimination::SetupReadyCheckObjectives()
{
	//bind the events for the ready check objectives
	TArray<AObjective*> AllPlayersReadyCheckObjectives;
	UObjectiveSystemBlueprintLibrary::GetObjectivesByTags(this, AllPlayersReadyCheckObjectiveTags, AllPlayersReadyCheckObjectives);

	//bind the events for the ready check objectives
	TArray<AObjective*> PlayerReadyCheckObjectives;
	UObjectiveSystemBlueprintLibrary::GetObjectivesByTags(this, PlayerReadyCheckObjectiveTags, PlayerReadyCheckObjectives);
		
	if (AllPlayersReadyCheckObjectives.IsValidIndex(0))
	{
		AllPlayersReadyObjectiveGroup = Cast<AObjectiveGroup>(AllPlayersReadyCheckObjectives[0]);
	}
	//set up All Players Ready objective group
	if (AllPlayersReadyObjectiveGroup)
	{
		UObjectiveSystemBlueprintLibrary::AddObjectivesToObjectiveGroup(this, PlayerReadyCheckObjectives, AllPlayersReadyObjectiveGroup);
		AllPlayersReadyObjectiveGroup->OnObjectiveComplete.AddUniqueDynamic(this, &ASOCGameMode_Elimination::OnAllPlayersReadyCheckObjectiveComplete);
		AllPlayersReadyObjectiveGroup->OnObjectiveFailed.AddUniqueDynamic(this, &ASOCGameMode_Elimination::OnAllPlayersReadyCheckObjectiveFailed);
	}
		
	for (AObjective* Objective : PlayerReadyCheckObjectives)
	{
		Objective->OnObjectiveComplete.AddUniqueDynamic(this, &ASOCGameMode_Elimination::OnReadyCheckObjectiveComplete);
		Objective->OnObjectiveFailure.AddUniqueDynamic(this, &ASOCGameMode_Elimination::OnReadyCheckObjectiveFailure);
	}
}

void ASOCGameMode_Elimination::OnReadyCheckObjectiveComplete(AObjective* Objective, AActor* Assignee, AActor* InInstigator)
{

}

void ASOCGameMode_Elimination::OnReadyCheckObjectiveFailure(AObjective* Objective, AActor* Assignee, AActor* InInstigator)
{
	
}

void ASOCGameMode_Elimination::OnAllPlayersReadyCheckObjectiveComplete(AObjective* Objective, AActor* Assignee, AActor* InInstigator)
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_StartMatch, this, &ASOCGameMode_Elimination::Timer_StartMatch, StartMatchTimerDuration, false);
}

void ASOCGameMode_Elimination::OnAllPlayersReadyCheckObjectiveFailed(AObjective* Objective, AActor* Assignee, AActor* InInstigator)
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_StartMatch);
}

void ASOCGameMode_Elimination::Timer_StartMatch()
{
	SetMatchState(MatchState::InProgress);
}

#pragma endregion

	
#pragma region Rematch Check

void ASOCGameMode_Elimination::SetupRematchObjectives()
{
	//bind the events for the rematch objectives
	TArray<AObjective*> AllPlayersRematchObjectives;
	UObjectiveSystemBlueprintLibrary::GetObjectivesByTags(this, AllPlayersRematchObjectiveTags, AllPlayersRematchObjectives);

	//bind the events for the rematch objectives
	TArray<AObjective*> PlayerRematchObjectives;
	UObjectiveSystemBlueprintLibrary::GetObjectivesByTags(this, PlayerRematchObjectiveTags, PlayerRematchObjectives);

	if (AllPlayersRematchObjectives.IsValidIndex(0))
	{
		AllPlayersRematchObjectiveGroup = Cast<AObjectiveGroup>(AllPlayersRematchObjectives[0]);
	}
	//set up All Players Ready objective group
	if (AllPlayersRematchObjectiveGroup)
	{
		UObjectiveSystemBlueprintLibrary::AddObjectivesToObjectiveGroup(this, PlayerRematchObjectives, AllPlayersRematchObjectiveGroup);
		AllPlayersRematchObjectiveGroup->OnObjectiveComplete.AddUniqueDynamic(this, &ASOCGameMode_Elimination::OnAllPlayersRematchObjectiveComplete);
		AllPlayersRematchObjectiveGroup->OnObjectiveFailed.AddUniqueDynamic(this, &ASOCGameMode_Elimination::OnAllPlayersRematchObjectiveFailed);
	}
		
	for (AObjective* Objective : PlayerRematchObjectives)
	{
		Objective->OnObjectiveComplete.AddUniqueDynamic(this, &ASOCGameMode_Elimination::OnRematchObjectiveComplete);
		Objective->OnObjectiveFailure.AddUniqueDynamic(this, &ASOCGameMode_Elimination::OnRematchObjectiveFailure);
	}
}

void ASOCGameMode_Elimination::OnRematchObjectiveComplete(AObjective* Objective, AActor* Assignee, AActor* InInstigator)
{
	
}

void ASOCGameMode_Elimination::OnRematchObjectiveFailure(AObjective* Objective, AActor* Assignee, AActor* InInstigator)
{
	
}
	
void ASOCGameMode_Elimination::OnAllPlayersRematchObjectiveComplete(AObjective* Objective, AActor* Assignee, AActor* InInstigator)
{
	
}

void ASOCGameMode_Elimination::OnAllPlayersRematchObjectiveFailed(AObjective* Objective, AActor* Assignee, AActor* InInstigator)
{
	
}

void ASOCGameMode_Elimination::Timer_Rematch()
{
	if (!AllPlayersRematchObjectiveGroup)
	{
		return;
	}

	if (AllPlayersRematchObjectiveGroup->IsObjectiveGroupComplete())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Rematch");
		//rematch
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Match ended, return to main menu");
		//end the match
	}
}
	
#pragma endregion

#pragma region Buildings

void ASOCGameMode_Elimination::OnBuildingDestroyed(ASOCBuilding* BuildingVictim, AActor* Attacker, AController* ControllerInstigator)
{
	if (!BuildingVictim)
	{
		return;
	}

	//GEngine->AddOnScreenDebugMessage(-1 , 5.f, FColor::Red, "Building Destroyed");

	UBuildingSubsystem* BuildingSubsystem = UBuildingSubsystem::Get(this);

	if (!BuildingSubsystem)
	{
		return;
	}

	if (!Attacker || !Attacker->Implements<UAttitudeInterface>())
	{
		return;
	}

	bool bRemainingEnemyBuildings = false;
	
	TArray<ASOCBuilding*> Buildings = BuildingSubsystem->GetAllBuildings();

	for (ASOCBuilding* Building : Buildings)
	{
		const EAttitude Attitude = IAttitudeInterface::Execute_GetAttitudeTowards(Attacker, Building);

		const bool bIsAlive = IHealthInterface::Execute_IsAlive(Building);

		if (bIsAlive && Attitude == EAttitude::Hostile)
		{
			bRemainingEnemyBuildings = true;
			break;
		}
	}

	if (!bRemainingEnemyBuildings)
	{
		UObjectiveSystemBlueprintLibrary::ProgressObjectivesForAssigneeByTags(ControllerInstigator, DestroyBuildingsObjectiveTags, true);
	}
}

void ASOCGameMode_Elimination::OnDestroyEnemyBuildingsObjectiveComplete(AObjective* Objective, AActor* Assignee, AActor* InInstigator)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Destroy Enemy Buildings Objective Complete" + Assignee->GetName() + " won the game!");

	SetMatchState(MatchState::WaitingPostMatch);
}

#pragma endregion

#pragma region Actor Death

void ASOCGameMode_Elimination::OnActorKilled(AActor* Victim, AActor* Attacker, AController* ControllerInstigator)
{
	Super::OnActorKilled(Victim, Attacker, ControllerInstigator);

	ASOCBuilding* BuildingVictim = Cast<ASOCBuilding>(Victim);

	if (BuildingVictim)
	{
		OnBuildingDestroyed(BuildingVictim, Attacker, ControllerInstigator);
	}
}

#pragma endregion