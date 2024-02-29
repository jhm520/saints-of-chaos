// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandComponent.h"

#include "CommandableComponent.h"

#pragma region Framework

// Sets default values for this component's properties
UCommandComponent::UCommandComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCommandComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCommandComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
#pragma endregion

#pragma region Command

bool UCommandComponent::Command(UCommandableComponent* Commandable, const FCommandInstance& Command)
{
	if (!Commandable)
	{
		return false;
	}

	return Commandable->GiveCommand(Command);
}

#pragma endregion

