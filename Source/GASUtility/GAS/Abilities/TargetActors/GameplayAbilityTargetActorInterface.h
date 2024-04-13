// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayAbilityTargetActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameplayAbilityTargetActorInterface : public UInterface
{
	GENERATED_BODY()
};

/** Interface for actors/abilities that can provide a target actor for a gameplay ability
 * 
 */
class GASUTILITY_API IGameplayAbilityTargetActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual AActor* GetTargetActor() const = 0;
};
