// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SOCAIFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SOCAI_API USOCAIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "SOCAI|Utility")
	static bool IsActorDirectedBy(const AActor* Actor, const AActor* Director);
	
};
