// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreUtilityBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class COREUTILITY_API UCoreUtilityBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	//returns the player controller id as it corresponds to the player array on the game state
	//returns -1 if the player controller is not found
	//must be called on the server
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, meta = (WorldContext = "WorldContextObject"), Category = "CoreUtility|Controller")
	static int32 GetAuthPlayerControllerId(const UObject* WorldContextObject, APlayerController* PlayerController);
	
};
