// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterInfoWidget.h"

void UCharacterInfoWidget::OnHealthChanged(float NewHealth, float MaxHealth)
{
	K2_OnHealthChanged(NewHealth, MaxHealth);
}
