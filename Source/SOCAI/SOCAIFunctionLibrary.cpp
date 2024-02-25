// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIFunctionLibrary.h"

#include "Components/SOCAIAvatarComponent.h"
#include "Interfaces/SOCAIBehaviorInterface.h"

bool USOCAIFunctionLibrary::IsActorDirectedBy(const AActor* Actor, const AActor* Director)
{
	if (!Actor || !Director)
	{
		return false;
	}

	const ISOCAIBehaviorInterface* BehaviorInterface = Cast<ISOCAIBehaviorInterface>(Actor);

	if (!BehaviorInterface)
	{
		return false;
	}

	USOCAIAvatarComponent* AvatarComponent = BehaviorInterface->GetAvatarComponent();

	if (!AvatarComponent)
	{
		return false;
	}

	APawn* DirectorPawn = AvatarComponent->GetDirectorPawn();

	if (!DirectorPawn)
	{
		return false;
	}

	if (DirectorPawn == Director)
	{
		return true;
	}

	if (DirectorPawn->GetOwner() == Director)
	{
		return true;
	}
	
	return false;
}
