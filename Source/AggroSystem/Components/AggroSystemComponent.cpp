// Fill out your copyright notice in the Description page of Project Settings.


#include "AggroSystemComponent.h"

// Sets default values for this component's properties
UAggroSystemComponent::UAggroSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UAggroSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UAggroSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}