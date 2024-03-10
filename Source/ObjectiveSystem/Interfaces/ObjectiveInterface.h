// Copyright [2022] Psychedelic Games. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectiveInterface.generated.h"

UINTERFACE(BlueprintType)
class OBJECTIVESYSTEM_API UObjectiveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Actors & Objects that implement this interface must be an objective of some sort of game mode
 */
class OBJECTIVESYSTEM_API IObjectiveInterface
{
	GENERATED_BODY()
public:
	// Getter function for the InventorySystemComponent variable
	UFUNCTION()
	virtual UObjectiveComponent* GetObjectiveComponent() const= 0;
};
