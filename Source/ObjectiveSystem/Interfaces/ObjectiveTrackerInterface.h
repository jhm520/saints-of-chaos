//

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectiveTrackerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UObjectiveTrackerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OBJECTIVESYSTEM_API IObjectiveTrackerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// returns the objective tracker component
	UFUNCTION()
	virtual UObjectiveTrackerComponent* GetObjectiveTrackerComponent() const= 0;
};
