// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectorComponent.h"

#pragma region Framework

// Sets default values for this component's properties
USelectorComponent::USelectorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USelectorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USelectorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#pragma endregion

#pragma region Selection

void USelectorComponent::Select(USelectableComponent* SelectableComponent)
{
	if (!SelectableComponent)
	{
		return;
	}

	SelectedComponents.AddUnique(SelectableComponent);
}

void USelectorComponent::Deselect(USelectableComponent* SelectableComponent)
{
	if (!SelectableComponent)
	{
		return;
	}

	SelectedComponents.Remove(SelectableComponent);
}

void USelectorComponent::ClearSelection()
{
	SelectedComponents.Empty();
}

#pragma endregion