// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SelectionSystemBlueprintLibrary.generated.h"

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
	
};
