// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectorComponent.h"
#include "SelectableComponent.h"
#include "Net/UnrealNetwork.h"

#pragma region Framework

// Sets default values for this component's properties
USelectorComponent::USelectorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);

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

void USelectorComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(USelectorComponent, SelectedComponents, COND_SkipOwner, REPNOTIFY_Always);

}

#pragma endregion

#pragma region Selection

void USelectorComponent::Select(USelectableComponent* SelectableComponent, bool bRepToServer)
{
	if (bRepToServer && !GetOwner()->HasAuthority())
	{
		ServerSelect(SelectableComponent);
	}
	
	if (!SelectableComponent)
	{
		return;
	}

	SelectedComponents.AddUnique(SelectableComponent);
}

void USelectorComponent::Deselect(USelectableComponent* SelectableComponent, bool bRepToServer)
{
	if (bRepToServer && !GetOwner()->HasAuthority())
	{
		ServerDeselect(SelectableComponent);
	}
	
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

void USelectorComponent::OnRep_SelectedComponents()
{
	
}

void USelectorComponent::ServerSelect_Implementation(USelectableComponent* SelectableComponent)
{
	Select(SelectableComponent);
}

void USelectorComponent::ServerDeselect_Implementation(USelectableComponent* SelectableComponent)
{
	Deselect(SelectableComponent);
}

#pragma endregion