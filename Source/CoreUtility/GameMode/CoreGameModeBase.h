// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CoreGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class COREUTILITY_API ACoreGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Player Start
	
protected:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
#pragma endregion
};
