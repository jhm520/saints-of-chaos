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

#pragma region Framework

ASOCGameMode_Elimination::ASOCGameMode_Elimination()
{
	bDelayedStart = true;
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
		for (UObjectiveInfoCollection* Collection : PreMatchObjectiveCollections)
		{
			UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByCollection(GameState, Collection, Assignees);
			UObjectiveSystemBlueprintLibrary::BeginObjectivesForActorByCollection(GameState, Collection);
		}

		for (UObjectiveInfoCollection* Collection : MatchObjectiveCollections)
		{
			UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByCollection(GameState, Collection, Assignees);
		}
	}
	else if (GetMatchState() == MatchState::InProgress)
	{
		for (UObjectiveInfoCollection* Collection : MatchObjectiveCollections)
		{
			UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByCollection(GameState, Collection, Assignees);
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
		UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByCollection(GameState, Collection, Assignees);
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
		UObjectiveSystemBlueprintLibrary::ProgressObjectivesForActorByTags(ControllerInstigator, DestroyBuildingsObjectiveTags, true);
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