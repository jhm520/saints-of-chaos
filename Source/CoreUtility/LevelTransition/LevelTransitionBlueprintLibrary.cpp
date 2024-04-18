// © 2024 John Henry Miller. All rights reserved

#include "LevelTransitionBlueprintLibrary.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ULevelTransitionBlueprintLibrary::TransitionLevel(UObject* WorldContextObject, const FName& InLevelName, TSubclassOf<AGameModeBase> InGameMode, ELevelNetworkingType InLevelNetworkingType, const FGameplayTagContainer LevelTransitionTags, const FString& OptionalIPAddress, int OptionalPort, FString InAdditionalOptions)
{
	if (!WorldContextObject)
	{
		return;
	}

	if (InLevelNetworkingType == ELevelNetworkingType::ListenServer)
	{
		InAdditionalOptions += "?listen";
	}

	if (InLevelNetworkingType == ELevelNetworkingType::Client)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(WorldContextObject, "open " + OptionalIPAddress + ":" + FString::FromInt(OptionalPort) + InAdditionalOptions);
		return;
	}
	
	const FString GameModeURL = InGameMode ? InGameMode->GetPathName() : "";

	const FString GameModeOptionString = "?game=" + GameModeURL;
	
	UGameplayStatics::OpenLevel(WorldContextObject, InLevelName, true, GameModeOptionString+InAdditionalOptions);
}
