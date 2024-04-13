// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageCauserInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageCauserInterface : public UInterface
{
	GENERATED_BODY()
};

/** This interface is to be added to any class that has some part in dealing damage
 * 
 */
class SOC_API IDamageCauserInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//return the controller that is ultimately responsible for this actor dealing damage
	UFUNCTION()
	virtual AController* GetDamageInstigatorController() const = 0;

};
