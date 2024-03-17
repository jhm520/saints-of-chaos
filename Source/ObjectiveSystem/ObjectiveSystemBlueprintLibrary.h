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
	//setup specified objectives on the specified Tracker actor, essentially informing all assignees of the objectives they need to complete
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Objectives")
	static void SetupObjectivesForActorByCollection(AActor* ObjectiveTracker, UObjectiveInfoCollection* ObjectiveCollection, TArray<AActor*> Assignees);

	//begin specified objectives for the specified Tracker actor, essentially informing all assignees of the objective that they should start working on completing the objective now
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Objectives")
	static void BeginObjectivesForActorByCollection(AActor* ObjectiveTracker, UObjectiveInfoCollection* ObjectiveCollection, const FGameplayTagContainer& OptionalTags = FGameplayTagContainer());
	
	//progress any objectives assigned to the assignee actor that have the specified tags
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Objectives")
	static void ProgressObjectivesForAssigneeByTags(AActor* Assignee, const FGameplayTagContainer& ObjectiveTags, bool bSuccess);
	
	//get any objectives that have the specified tags
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(WorldContext="WorldContextObject"), Category = "Objectives")
	static void GetObjectivesByTags(UObject* WorldContextObject, const FGameplayTagContainer ObjectiveTags, TArray<AObjective*>& OutObjectives);

	//get any objectives that have the specified tags
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(WorldContext="WorldContextObject"), Category = "Objectives")
	static bool GetAssignedObjectives(UObject* WorldContextObject, AActor* Assignee, TArray<AObjective*>& OutObjectives, FGameplayTagContainer ObjectiveTags = FGameplayTagContainer());
	
};
