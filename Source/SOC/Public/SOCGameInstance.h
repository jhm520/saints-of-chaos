// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SOCGameInstance.generated.h"

/**
 * 
 */
class UWhatsMyPublicIP;
UCLASS()
class SOC_API USOCGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	TObjectPtr<UWhatsMyPublicIP> PublicIPObject = nullptr;

	virtual void Init() override;

	UFUNCTION()
	void OnReceievedPublicIP(FString InPublicIP);

	UPROPERTY(BlueprintReadOnly, Category = "Networking")
	FString PublicIPAddress = "";
	
};
