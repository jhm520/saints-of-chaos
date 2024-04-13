// © 2024 John Henry Miller. All rights reserved

#include "SOCGameInstance.h"

#include "WhatsMyPublicIP.h"

void USOCGameInstance::Init()
{
	Super::Init();

	PublicIPObject = NewObject<UWhatsMyPublicIP>(this);

	if (PublicIPObject)
	{
		PublicIPObject->OnIPAddressReceived.AddDynamic(this, &USOCGameInstance::OnReceievedPublicIP);
		PublicIPObject->GetMyPublicIP();
	}
	
}

void USOCGameInstance::OnReceievedPublicIP(FString InPublicIP)
{
	PublicIPAddress = InPublicIP;
}

#pragma region Game State

void USOCGameInstance::OnGameStateHasBegunPlay_Implementation(AGameStateBase* GameState)
{
	OnGameStateHasBegunPlayDelegate.Broadcast(GameState);
}

#pragma endregion
