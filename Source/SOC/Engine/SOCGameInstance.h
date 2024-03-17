// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SOCGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateHasBegunPlayDelegate, AGameStateBase* /*MatchState*/, GameState);

/**
 * 
 */
class UWhatsMyPublicIP;
UCLASS()
class SOC_API USOCGameInstance : public UGameInstance
{
	GENERATED_BODY()

#pragma region Framework
public:
	virtual void Init() override;

#pragma endregion

#pragma region Public IP

public:
	TObjectPtr<UWhatsMyPublicIP> PublicIPObject = nullptr;


	UFUNCTION()
	void OnReceievedPublicIP(FString InPublicIP);

	UPROPERTY(BlueprintReadOnly, Category = "Networking")
	FString PublicIPAddress = "";

#pragma endregion


#pragma region Game State

	UFUNCTION(BlueprintNativeEvent, Category = "Game State")
	void OnGameStateHasBegunPlay(AGameStateBase* GameState);

	UPROPERTY(BlueprintAssignable)
	FOnGameStateHasBegunPlayDelegate OnGameStateHasBegunPlayDelegate;

#pragma endregion
	
};
