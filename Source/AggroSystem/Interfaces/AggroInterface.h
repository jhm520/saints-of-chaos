#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AggroInterface.generated.h"

UINTERFACE(BlueprintType)
class AGGROSYSTEM_API UAggroInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Describes the attitude of an actor towards other actors
 */
class AGGROSYSTEM_API IAggroInterface
{
	GENERATED_BODY()
public:

};
