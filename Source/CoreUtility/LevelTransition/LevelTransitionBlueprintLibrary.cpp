
#include "LevelTransitionBlueprintLibrary.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ULevelTransitionBlueprintLibrary::TransitionLevel(UObject* WorldContextObject, TSubclassOf<AGameModeBase> InGameMode, ELevelNetworkingType InLevelNetworkingType, const FName& InLevelName, const FGameplayTagContainer LevelTransitionTags, const FString& OptionalIPAddress, int OptionalPort, FString InAdditionalOptions)
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
