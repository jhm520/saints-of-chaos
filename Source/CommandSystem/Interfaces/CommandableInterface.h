// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CommandableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCommandableInterface : public UInterface
{
	GENERATED_BODY()
};

class UCommandableComponent;
/** This is an interface for actors that are selectable
 * 
 */
class COMMANDSYSTEM_API ICommandableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UCommandableComponent* GetCommandableComponent() const = 0;

	UFUNCTION(BlueprintNativeEvent, Category = "Command", meta=(DisplayName="On Command Begin"))
	void OnCommandBegin(const FCommandInstance& Command);

	UFUNCTION(BlueprintNativeEvent, Category = "Command", meta=(DisplayName="Check Command Finished"))
	bool CheckCommandFinished(const FCommandInstance& Command) const;
};
