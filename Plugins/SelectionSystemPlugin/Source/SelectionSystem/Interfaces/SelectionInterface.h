// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USelectionInterface : public UInterface
{
	GENERATED_BODY()
};

/** This is an interface for various other actors that care when things get selected or deselected by selectors
 *  these may need to be called manually
 */
class SELECTIONSYSTEM_API ISelectionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Selection")
	void OnSelected(AActor* Selector, AActor* Selected);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Selection")
	void OnDeselected(AActor* Selector, AActor* Selected);
};
