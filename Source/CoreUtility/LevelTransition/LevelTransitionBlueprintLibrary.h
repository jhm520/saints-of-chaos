// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "LevelTransitionBlueprintLibrary.generated.h"

UENUM(BlueprintType)
enum class ELevelNetworkingType : uint8
{
	Standalone,
	DedicatedServer,
	ListenServer,
	Client
};

/**
 * 
 */
UCLASS()
class COREUTILITY_API ULevelTransitionBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Level Transition")
	static void TransitionLevel(UObject* WorldContextObject, const FName& InLevelName, TSubclassOf<AGameModeBase> InGameMode, ELevelNetworkingType InLevelNetworkingType, const FGameplayTagContainer LevelTransitionTags = FGameplayTagContainer(), const FString& InAdditionalOptions = "");
};
