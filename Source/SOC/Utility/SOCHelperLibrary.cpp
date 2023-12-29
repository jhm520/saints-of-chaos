// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCHelperLibrary.h"

#include "SOC/Engine/SOCGameInstance.h"
#include "SocketSubsystem.h"

bool USOCHelperLibrary::GetLocalIPAddress(UObject* WorldContextObject, FString& OutIPAddress)
{
	AActor* CallingActor = Cast<AActor>(WorldContextObject);

	if (!CallingActor)
	{
		return false;
	}
	
	FString IpAddr("NONE");
	
	bool canBind = false;
	const TSharedRef<FInternetAddr> LocalIP = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog,canBind);
	
	if(LocalIP->IsValid())
	{
		OutIPAddress = LocalIP->ToString(true);//If you want to add a port, write true
		return true;
	}
	
		
	return false;
}

bool USOCHelperLibrary::GetPublicIPAddress(UObject* WorldContextObject, FString& OutIPAddress)
{
	if (!WorldContextObject)
	{
		return false;
	}

	UWorld* World = WorldContextObject->GetWorld();

	if (!World)
	{
		return false;
	}

	USOCGameInstance* GameInst = World->GetGameInstance<USOCGameInstance>();

	if (!GameInst)
	{
		return false;
	}

	OutIPAddress = GameInst->PublicIPAddress;

	return OutIPAddress.Len() > 0;
}
