// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCHUD.h"

#include "Widgets/ReadyCheckWidget.h"
#include "Widgets/BoxSelectWidget.h"
#pragma region Framework

void ASOCHUD::Reset()
{
	Super::Reset();

	if (IsValid(ReadyCheckWidget))
	{
		ReadyCheckWidget->RemoveFromParent();
		ReadyCheckWidget = nullptr;
	}

	if (IsValid(RematchCheckWidget))
	{
		RematchCheckWidget->RemoveFromParent();
		RematchCheckWidget = nullptr;
	}

	if (IsValid(BoxSelectWidget))
	{
		BoxSelectWidget->RemoveFromParent();
		BoxSelectWidget = nullptr;
	}
}

#pragma endregion 