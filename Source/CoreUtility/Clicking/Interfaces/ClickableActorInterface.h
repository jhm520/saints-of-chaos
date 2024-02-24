// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreUtility/Clicking/Components/ClickableActorComponent.h"
#include "UObject/Interface.h"
#include "ClickableActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UClickableActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COREUTILITY_API IClickableActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UPrimitiveComponent* GetClickableComponent() const = 0;

	virtual UClickableActorComponent* GetClickableActorComponent() const = 0;
};