// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectableComponent.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

#pragma region Framework

// Sets default values for this component's properties
USelectableComponent::USelectableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	SetIsReplicatedByDefault(true);

	// ...
}

// Called when the game starts
void USelectableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void USelectableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
#pragma endregion

#pragma region Selectable

void USelectableComponent::OnSelected()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, GetOwner()->GetName() + TEXT(" Selected"));
}

void USelectableComponent::OnDeselected()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, GetOwner()->GetName() + TEXT(" Deselected"));
}

#pragma endregion