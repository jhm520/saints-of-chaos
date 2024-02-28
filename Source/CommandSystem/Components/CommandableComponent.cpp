// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandableComponent.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

#pragma region Framework

// Sets default values for this component's properties
UCommandableComponent::UCommandableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	SetIsReplicatedByDefault(true);

	// ...
}

// Called when the game starts
void UCommandableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UCommandableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
#pragma endregion