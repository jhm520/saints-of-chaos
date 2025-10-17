// © 2024 Jade Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "ReadyCheckWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API UReadyCheckWidget : public UCommonUserWidget
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
