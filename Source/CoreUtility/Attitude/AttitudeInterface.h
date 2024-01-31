#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttitudeInterface.generated.h"

/*
 * The attitude of an actor
 **/
UENUM(BlueprintType)
enum class EAttitude : uint8
{
	Friendly,
	Neutral,
	Hostile,
};

UINTERFACE(BlueprintType)
class COREUTILITY_API UAttitudeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Describes the attitude of an actor towards other actors
 */
class COREUTILITY_API IAttitudeInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EAttitude GetAttitudeTowards(AActor* Other) const;
};
