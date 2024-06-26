// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "SortableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USortableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COREUTILITY_API ISortableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	//Returns true if the actor is sorted before the other actor, false otherwise
	virtual bool Compare(const AActor* OtherActor, FGameplayTag SortTag, bool bDescending) const = 0;
};
