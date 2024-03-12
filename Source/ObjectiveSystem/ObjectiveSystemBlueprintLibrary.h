// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "ObjectiveSystemBlueprintLibrary.generated.h"

class UObjectiveInfoCollection;
/**
 * 
 */
UCLASS()
class OBJECTIVESYSTEM_API UObjectiveSystemBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Objectives")
	static void SetupObjectivesForActorByCollection(AActor* ObjectiveTracker, UObjectiveInfoCollection* ObjectiveCollection, TArray<AActor*> Assignees);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Objectives")
	static void BeginObjectivesForActorByCollection(AActor* ObjectiveTracker, UObjectiveInfoCollection* ObjectiveCollection, const FGameplayTagContainer& OptionalTags = FGameplayTagContainer());
	
};
