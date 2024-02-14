// Fill out your copyright notice in the Description page of Project Settings.

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
	virtual bool CanPlayerSpawnAt(APlayerController* PlayerController) const = 0;
};