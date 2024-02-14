// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStartBase.h"

#include "CoreUtility/CoreUtilityBlueprintLibrary.h"

#pragma region Framework

APlayerStartBase::APlayerStartBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerControllerId = -1;
}

#pragma endregion

#pragma region Player Start Interface

bool APlayerStartBase::CanPlayerSpawnAt(APlayerController* PlayerController) const
{
	if (!PlayerController)
	{
		return false;
	}

	if (PlayerControllerId == -1)
	{
		return true;
	}
	
	const int32 LocalPlayerControllerId = UCoreUtilityBlueprintLibrary::GetAuthPlayerControllerId(this, PlayerController);

	return LocalPlayerControllerId == PlayerControllerId;
}

#pragma endregion