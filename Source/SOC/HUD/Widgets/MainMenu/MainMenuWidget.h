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

#pragma region Ready Check
protected:
	UFUNCTION(BlueprintCallable, Category = "Ready Check")
	void OnSetReady(bool bIsReady);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ready Check")
	FGameplayTagContainer ReadyCheckTags;
#pragma endregion
};
