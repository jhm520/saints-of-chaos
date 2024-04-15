// © 2024 John Henry Miller. All rights reserved

#include "LevelTransitionBlueprintLibrary.h"

#include "Kismet/GameplayStatics.h"

void ULevelTransitionBlueprintLibrary::TransitionLevel(UObject* WorldContextObject, const FName& InLevelName, TSubclassOf<AGameModeBase> InGameMode, ELevelNetworkingType InLevelNetworkingType, const FGameplayTagContainer LevelTransitionTags, const FString& InOptions)
{
	if (!WorldContextObject)
	{
		return;
	}
	
	UGameplayStatics::OpenLevel(WorldContextObject, InLevelName, true, InOptions);
}
