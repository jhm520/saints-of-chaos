// © 2024 Jade Miller. All rights reserved

#include "MainMenuWidget.h"

#include "CoreUtility/LevelTransition/LevelTransitionBlueprintLibrary.h"
#include "ObjectiveSystem/ObjectiveSystemBlueprintLibrary.h"
#include "ObjectiveSystem/Interfaces/ObjectiveAssigneeInterface.h"
#include "SOC/Engine/SOCGameInstance.h"


#pragma region Solo Play Button
void UMainMenuWidget::OnPressedSoloPlay()
{
	ULevelTransitionBlueprintLibrary::TransitionLevel(this, SoloGameMode, ELevelNetworkingType::Standalone, SoloGameMap, FGameplayTagContainer(), FString());
}
#pragma endregion

#pragma region Host Game Button
void UMainMenuWidget::OnPressedHostGame()
{
	ULevelTransitionBlueprintLibrary::TransitionLevel(this, SoloGameMode, ELevelNetworkingType::ListenServer, SoloGameMap,FGameplayTagContainer(), FString());
}

#pragma endregion

#pragma region Join Game Button
void UMainMenuWidget::OnPressedJoinGame()
{
	// USOCGameInstance* GameInstance = Cast<USOCGameInstance>(GetGameInstance());
	//
	// if (!GameInstance)
	// {
	// 	return;
	// }
	//
	 const FString& IPAddress = GetJoinGameIP();
	ULevelTransitionBlueprintLibrary::TransitionLevel(this, SoloGameMode, ELevelNetworkingType::Client, SoloGameMap, FGameplayTagContainer(), IPAddress, 7777, FString());
}

#pragma endregion