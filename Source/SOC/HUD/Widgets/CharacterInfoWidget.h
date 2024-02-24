// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CoreUtility/Attitude/AttitudeInterface.h"
#include "CharacterInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API UCharacterInfoWidget : public UCommonUserWidget
{
	GENERATED_BODY()
#pragma region Health

public:
	virtual void OnHealthChanged(float NewHealth, float MaxHealth);

protected:
	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnHealthChanged", Category = "Character Info")
	void K2_OnHealthChanged(float NewHealth, float MaxHealth);
#pragma endregion

#pragma region Attitude
public:
	virtual void UpdatePlayerAttitude(EAttitude NewAttitude);
protected:
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Update Player Attitude"))
	void K2_UpdatePlayerAttitude(EAttitude NewAttitude);

	UPROPERTY()
	EAttitude Attitude = EAttitude::Neutral;
#pragma endregion
};
