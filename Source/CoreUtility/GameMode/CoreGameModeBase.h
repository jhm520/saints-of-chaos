// © 2024 John Henry Miller. All rights reserved
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
