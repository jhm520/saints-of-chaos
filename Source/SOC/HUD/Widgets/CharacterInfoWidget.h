// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CharacterInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API UCharacterInfoWidget : public UCommonUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void OnHealthChanged(float NewHealth, float MaxHealth);

protected:
	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnHealthChanged", Category = "Character Info")
	void K2_OnHealthChanged(float NewHealth, float MaxHealth);

};
