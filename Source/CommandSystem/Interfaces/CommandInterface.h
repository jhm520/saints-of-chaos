// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CommandInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCommandInterface : public UInterface
{
	GENERATED_BODY()
};

class UCommandComponent;
/**
 * 
 */
class COMMANDSYSTEM_API ICommandInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION()
	virtual UCommandComponent* GetCommandComponent() const = 0;
};
