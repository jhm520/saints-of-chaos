// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WhatsMyPublicIP.h"
#include "SOCGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateHasBegunPlayDelegate, AGameStateBase* /*MatchState*/, GameState);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FIPDelegate, FString, IP );

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
	UPROPERTY(BlueprintReadWrite, Category = "Networking")
	TObjectPtr<UWhatsMyPublicIP> PublicIPObject = nullptr;

	UPROPERTY(BlueprintAssignable, Category = "Networking")
	FIPDelegate OnIPAddressReceived;

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
