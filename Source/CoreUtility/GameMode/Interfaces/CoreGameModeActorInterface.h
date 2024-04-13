// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CoreGameModeActorInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCoreGameModeActorInterface : public UInterface
{
	GENERATED_BODY()
};

/** Actors that implement this interface will indicate to any existing AutoOwnershipComponents that they are candidates for ownership
 * 
 */
class COREUTILITY_API ICoreGameModeActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual bool ShouldReset(AActor* Actor) const { return true;};
};
