// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CoreUtility/Attitude/AttitudeInterface.h"
#include "BoxSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API UBoxSelectWidget : public UCommonUserWidget
{
	GENERATED_BODY()
#pragma region Box Select

public:
	virtual void OnBoxSelectInput(bool bPressed);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnBoxSelectInput", Category = "Box Select")
	void K2_OnBoxSelectInput(bool bPressed);
};
