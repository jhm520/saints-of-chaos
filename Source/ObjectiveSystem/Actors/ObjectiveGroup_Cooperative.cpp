// © 2024 John Henry Miller. All rights reserved

#include "ObjectiveGroup_Cooperative.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"
#include "ObjectiveSystem/ObjectiveSystemBlueprintLibrary.h"

void AObjectiveGroup_Cooperative::SetupSubObjectives_Implementation()
{
	TArray<AActor*> Assignees;

	GetObjectiveGroupAssignees(Assignees);

	//create one sub objective for each assignee
	for (AActor* Assignee : Assignees)
	{
		if (!Assignee)
		{
			return;
		}

		TArray<AActor*> SubObjectiveAssignees = {Assignee};
		
		TArray<AObjective*> LocalSubObjectives;
		UObjectiveSystemBlueprintLibrary::SetupObjectivesForActorByTags(Assignee, SubObjectiveTags, SubObjectiveAssignees, LocalSubObjectives);

		for (AObjective* SubObjective : LocalSubObjectives)
		{
			AddSubObjective(SubObjective);
		}
	}
}

void AObjectiveGroup_Cooperative::GetObjectiveGroupAssignees_Implementation(TArray<AActor*>& OutAssignees)
{
	AGameStateBase* GameState = GetWorld()->GetGameState();

	if (!GameState)
	{
		return;
	}

	for (APlayerState* PlayerState : GameState->PlayerArray)
	{
		if (PlayerState)
		{
			OutAssignees.Add(PlayerState);
		}
	}
}
