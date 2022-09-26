// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SOCHelperLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API USOCHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(WorldContext="WorldContextObject"), Category = "Networking")
	static bool GetLocalIPAddress(UObject* WorldContextObject, FString& OutIPAddress);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(WorldContext="WorldContextObject"), Category = "Networking")
	static bool GetPublicIPAddress(UObject* WorldContextObject, FString& OutIPAddress);
	
};
