// © 2024 John Henry Miller. All rights reserved

#include "CharacterInfoWidget.h"

#include "CoreUtility/Attitude/AttitudeInterface.h"

void UCharacterInfoWidget::OnHealthChanged(float NewHealth, float MaxHealth)
{
	K2_OnHealthChanged(NewHealth, MaxHealth);
}

void UCharacterInfoWidget::UpdatePlayerAttitude(EAttitude NewAttitude)
{
	Attitude = NewAttitude;
	
	K2_UpdatePlayerAttitude(NewAttitude);
}
