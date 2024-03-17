// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "SortingBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class COREUTILITY_API USortingBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	//sorts an array of actors by an algorithm provided by the SortableInterface, with an input tag
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "CoreUtility|Sorting")
	static void SortActorArray(const UObject* WorldContextObject, const FGameplayTag SortTag, const TArray<AActor*>& InArray, TArray<AActor*>& OutArray, bool bDescending = true);
	
};
