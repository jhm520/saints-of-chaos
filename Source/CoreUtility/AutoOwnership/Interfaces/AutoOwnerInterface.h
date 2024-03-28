// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CoreUtility/AutoOwnership/Components/AutoOwnershipComponent.h"
#include "AutoOwnerInterface.generated.h"

UINTERFACE(MinimalAPI)
class UAutoOwnerInterface : public UInterface
{
	GENERATED_BODY()
};

/** Actors that implement this interface will indicate to any existing AutoOwnershipComponents that they are candidates for ownership
 * 
 */
class COREUTILITY_API IAutoOwnerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual UAutoOwnershipComponent* GetAutoOwnershipComponent() const = 0;
};
