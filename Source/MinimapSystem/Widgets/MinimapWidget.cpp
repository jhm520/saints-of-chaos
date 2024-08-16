// © 2024 Jade Miller. All rights reserved


#include "MinimapWidget.h"

#include "MinimapSystem/MinimapSubsystem.h"

#pragma region Framework
void UMinimapWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UMinimapSubsystem* MinimapSubsystem = UMinimapSubsystem::Get(GetWorld());

	if (MinimapSubsystem)
	{
		MinimapSubsystem->OnMinimapItemRegistered.AddDynamic(this, &UMinimapWidget::OnMinimapItemRegistered);
		MinimapSubsystem->OnMinimapItemUnregistered.AddDynamic(this, &UMinimapWidget::OnMinimapItemUnregistered);
	}
}

void UMinimapWidget::OnMinimapItemRegistered(UMinimapItemComponent* MinimapItem)
{
	// Implement your logic here
	K2_OnMinimapItemRegistered(MinimapItem);
	
}

void UMinimapWidget::OnMinimapItemUnregistered(UMinimapItemComponent* MinimapItem)
{
	// Implement your logic here
	K2_OnMinimapItemUnregistered(MinimapItem);
}
#pragma endregion