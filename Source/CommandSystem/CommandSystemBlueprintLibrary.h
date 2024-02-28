// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/CommandableComponent.h"
#include "CommandSystemBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDSYSTEM_API UCommandSystemBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Selection")
	static bool CommandActor(AActor* CommanderActor, AActor* CommandedActor, const FCommandInfo& Command);
	
	UFUNCTION(BlueprintCallable, Category = "Selection")
	static FCommandInfo MakeCommand(AActor* CommanderActor, const FGameplayTag& CommandTag, AActor* TargetActor = nullptr, const FVector& TargetLocation = FVector::ZeroVector);
	
};
