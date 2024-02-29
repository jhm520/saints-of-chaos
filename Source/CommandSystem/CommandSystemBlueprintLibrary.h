// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "CommandSystemBlueprintLibrary.generated.h"

class UCommandInfo;
class UCommandableComponent;

//struct to represent an AIController's current action
USTRUCT(BlueprintType)
struct COMMANDSYSTEM_API FCommandInstance
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	AActor* Commander = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	const UCommandInfo* CommandInfo = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	AActor* TargetActor = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	FVector_NetQuantize TargetLocation = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	FGuid Guid = FGuid();

	bool IsValid() const
	{
		return Commander != nullptr && CommandInfo != nullptr;
	}

	friend bool operator==(const FCommandInstance& A, const FCommandInstance& B)
	{
		return A.Guid == B.Guid;
	}
	
	FCommandInstance(){}
};

/**
 * 
 */
UCLASS()
class COMMANDSYSTEM_API UCommandSystemBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Selection")
	static bool CommandActor(AActor* CommanderActor, AActor* CommandedActor, const FCommandInstance& Command);
	
	UFUNCTION(BlueprintCallable, Category = "Selection")
	static FCommandInstance MakeCommand(AActor* CommanderActor, const FGameplayTag& CommandTag, AActor* TargetActor = nullptr, const FVector& TargetLocation = FVector::ZeroVector);
	
};
