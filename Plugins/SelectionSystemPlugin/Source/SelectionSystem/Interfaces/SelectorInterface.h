// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectorInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USelectorInterface : public UInterface
{
	GENERATED_BODY()
};

class USelectorComponent;

/** This is an interface for actors that care about selecting
 * 
 */
class SELECTIONSYSTEM_API ISelectorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual USelectorComponent* GetSelectorComponent() const = 0;
};
