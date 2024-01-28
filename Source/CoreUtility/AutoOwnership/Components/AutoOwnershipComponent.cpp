// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoOwnershipComponent.h"

#include "CoreUtility/AutoOwnership/Interfaces/AutoOwnershipInterface.h"
#include "Kismet/GameplayStatics.h"

#pragma region Framework

// Sets default values for this component's properties
UAutoOwnershipComponent::UAutoOwnershipComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UAutoOwnershipComponent::BeginPlay()
{
	Super::BeginPlay();

	AutoTakeOwnership();

	// ...
	
}


// Called every frame
void UAutoOwnershipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#pragma endregion

#pragma region Auto Ownership

void UAutoOwnershipComponent::AutoTakeOwnership()
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GWorld, UAutoOwnershipInterface::StaticClass(), Actors);

	for (AActor* Actor : Actors)
	{
		IAutoOwnershipInterface* AutoOwnershipInterface = Cast<IAutoOwnershipInterface>(Actor);
		if (!AutoOwnershipInterface)
		{
			continue;
		}

		//if the owner of this component can't take ownership of the actor, skip it
		if (!AutoOwnershipInterface->CanTakeOwnership(GetOwner()))
		{
			continue;
		}
		
		Actor->SetOwner(GetOwner());
	}
}

#pragma endregion