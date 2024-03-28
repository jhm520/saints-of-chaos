// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CoreGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class COREUTILITY_API ACoreGameModeBase : public AGameMode
{
	GENERATED_BODY()

#pragma region Reset

	virtual bool ShouldReset_Implementation(AActor* ActorToReset) override;
#pragma endregion


#pragma region Player Start
	
protected:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
#pragma endregion
};
