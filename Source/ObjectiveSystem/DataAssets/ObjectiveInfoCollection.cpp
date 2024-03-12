//


#include "ObjectiveInfoCollection.h"
#include "ObjectiveSystem/Actors/Objective.h"

const FGameplayTagContainer UObjectiveInfoCollection::GetAllObjectiveTags() const
{
	FGameplayTagContainer AllTags;

	for (const FObjectiveInfo& ObjectiveInfo : ObjectiveInfoArray)
	{
		AllTags.AppendTags(ObjectiveInfo.ObjectiveTags);

		if (!ObjectiveInfo.ObjectiveClass)
		{
			continue;
		}

		AObjective* Objective = ObjectiveInfo.ObjectiveClass.GetDefaultObject();

		if (!Objective)
		{
			continue;
		}

		AllTags.AppendTags(Objective->ObjectiveTags);
	}

	return AllTags;
}