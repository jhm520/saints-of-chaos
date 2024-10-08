// © 2024 Jade Miller. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MinimapWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINIMAPSYSTEM_API UMinimapWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Framework
protected:
	virtual void NativeConstruct() override;

#pragma endregion

#pragma region Minimap
protected:
	UFUNCTION()
	void OnMinimapItemRegistered(UMinimapItemComponent* MinimapItem);
	
	UFUNCTION()
	void OnMinimapItemUnregistered(UMinimapItemComponent* MinimapItem);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Minimap")
	void K2_OnMinimapItemRegistered(UMinimapItemComponent* MinimapItem);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Minimap")
	void K2_OnMinimapItemUnregistered(UMinimapItemComponent* MinimapItem);

#pragma endregion

};
