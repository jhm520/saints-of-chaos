//

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectiveAssigneeInterface.generated.h"

class UObjectiveAssigneeComponent;

UINTERFACE(BlueprintType)
class OBJECTIVESYSTEM_API UObjectiveAssigneeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Actors & Objects that implement this interface must be an objective of some sort of game mode
 */
class OBJECTIVESYSTEM_API IObjectiveAssigneeInterface
{
	GENERATED_BODY()
public:
	// Getter function for the ObjectiveAssigneeComponent variable
	UFUNCTION()
	virtual UObjectiveAssigneeComponent* GetObjectiveAssigneeComponent() const= 0;

	// Getter function for the ObjectiveAssigneeComponent variable
	UFUNCTION()
	virtual AActor* GetAssignee() = 0;
};
