// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "CoreUtility/PlayerStart/Interfaces/PlayerStartInterface.h"
#include "PlayerStartBase.generated.h"

/**
 * 
 */
UCLASS()
class COREUTILITY_API APlayerStartBase : public APlayerStart, public IPlayerStartInterface
{
	GENERATED_BODY()

#pragma region Framework
protected:
	APlayerStartBase(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Player Start

protected:
	//actors that spawn at this player start will be controlled by the player controller with this id
	//if set to -1, any player controller can spawn here
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Start")
	int32 PlayerControllerId;

#pragma endregion

#pragma region Player Start Interface

	virtual bool CanPlayerSpawnAt(APlayerController* PlayerController) const override;

#pragma endregion

};
