// Fill out your copyright notice in the Description page of Project Settings.


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
