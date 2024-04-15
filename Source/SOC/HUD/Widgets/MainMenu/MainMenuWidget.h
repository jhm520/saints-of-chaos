// Copyright (c) 2024 John Henry Miller (jhm520@gmail.com) All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API UMainMenuWidget : public UCommonUserWidget
{
	GENERATED_BODY()

#pragma region Solo Play Button
public:
	UFUNCTION(BlueprintCallable, Category = "Ready Check")
	void OnPressedSoloPlay();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ready Check")
	TSubclassOf<AGameModeBase> SoloGameMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ready Check")
	FName SoloGameMap;
#pragma endregion
};
