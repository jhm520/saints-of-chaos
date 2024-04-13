// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpawnedActorInterface.generated.h"

UINTERFACE(MinimalAPI)
class USpawnedActorInterface : public UInterface
{
	GENERATED_BODY()
};

/** Actors that implement this interface will indicate to any existing AutoOwnershipComponents that they are candidates for ownership
 * 
 */
class COREUTILITY_API ISpawnedActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Called when the actor spawn is deferred and before it is finished spawning
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spawned Actor Interface")
	bool PreActorSpawnFinished(AActorSpawner* Spawner) const;

	// Called when the actor spawn is finished
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spawned Actor Interface")
	bool PostActorSpawnFinished(AActorSpawner* Spawner) const;
};
