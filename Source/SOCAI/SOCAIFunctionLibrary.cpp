// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIFunctionLibrary.h"

#include "Components/SOCAIBehaviorComponent.h"
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

	USOCAIBehaviorComponent* BehaviorComponent = BehaviorInterface->GetBehaviorComponent();

	if (!BehaviorComponent)
	{
		return false;
	}

	AActor* LocalDirector = BehaviorComponent->GetDirector();

	if (!LocalDirector)
	{
		return false;
	}

	if (LocalDirector == Director)
	{
		return true;
	}
	
	return false;
}
