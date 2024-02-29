// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "CommandSubsystem.generated.h"

class UCommandInfo;

/**
 * 
 */
UCLASS()
class COMMANDSYSTEM_API UCommandSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
friend class UCommandComponent;
friend class UCommandSystemBlueprintLibrary;
	
#pragma region Framework
	UFUNCTION(BlueprintPure, Category = "Attitude")
	static UCommandSubsystem* Get(const UObject* WorldContext);
#pragma endregion

#pragma region Command
	
protected:
	void AddCommand(UCommandInfo* CommandInfo);
	
	void RemoveCommand(UCommandInfo* CommandInfo);

	const UCommandInfo* GetCommand(const FGameplayTag& CommandTag) const;
	
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UCommandInfo>> CommandMap;
	
#pragma endregion
	
};
