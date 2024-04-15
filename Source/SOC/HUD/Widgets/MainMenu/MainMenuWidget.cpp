// © 2024 John Henry Miller. All rights reserved

#include "MainMenuWidget.h"

#include "CoreUtility/LevelTransition/LevelTransitionBlueprintLibrary.h"
#include "ObjectiveSystem/ObjectiveSystemBlueprintLibrary.h"
#include "ObjectiveSystem/Interfaces/ObjectiveAssigneeInterface.h"


#pragma region Solo Play Button
void UMainMenuWidget::OnPressedSoloPlay()
{
	ULevelTransitionBlueprintLibrary::TransitionLevel(this, SoloGameMap, SoloGameMode, ELevelNetworkingType::Standalone, FGameplayTagContainer(), FString());
}
#pragma endregion