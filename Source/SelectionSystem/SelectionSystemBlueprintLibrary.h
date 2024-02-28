// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SelectionSystemBlueprintLibrary.generated.h"

class USelectableComponent;
/**
 * 
 */
UCLASS()
class SELECTIONSYSTEM_API USelectionSystemBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Selection")
	static void SelectActor(AActor* Selector, const AActor* SelectedActor, bool bRepToServer = true);

	UFUNCTION(BlueprintCallable, Category = "Selection")
	static void ClearSelection(AActor* Selector, bool bRepToServer = true);

	UFUNCTION(BlueprintCallable, Category = "Selection")
	static void GetSelectedComponents(AActor* Selector, TArray<USelectableComponent*>& OutSelectedComponents);
	
};
