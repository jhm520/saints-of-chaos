// © 2024 John Henry Miller. All rights reserved

#include "SelectableComponent.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "SelectionSystem/Interfaces/SelectionInterface.h"

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

void USelectableComponent::OnSelected(AActor* Selector)
{
	OnSelectedDelegate.Broadcast(Selector);

	TArray<AActor*> ChildActors;
	GetOwner()->GetAllChildActors(ChildActors);

	for (AActor* ChildActor : ChildActors)
	{
		if (!ChildActor)
		{
			continue;
		}

		if (!ChildActor->Implements<USelectionInterface>())
		{
			continue;
		}

		ISelectionInterface::Execute_OnSelected(ChildActor, Selector, GetOwner());
	}
}

void USelectableComponent::OnDeselected(AActor* Selector)
{
	OnDeselectedDelegate.Broadcast(Selector);

	TArray<AActor*> ChildActors;
	GetOwner()->GetAllChildActors(ChildActors);

	for (AActor* ChildActor : ChildActors)
	{
		if (!ChildActor)
		{
			continue;
		}

		if (!ChildActor->Implements<USelectionInterface>())
		{
			continue;
		}

		ISelectionInterface::Execute_OnDeselected(ChildActor, Selector, GetOwner());
	}
}

#pragma endregion