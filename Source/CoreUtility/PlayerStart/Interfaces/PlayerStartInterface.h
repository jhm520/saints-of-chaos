// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerStartInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerStartInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COREUTILITY_API IPlayerStartInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	//Returns true if the player can spawn at this player start
	virtual bool CanPlayerSpawnAt(AController* Controller) const = 0;
};
