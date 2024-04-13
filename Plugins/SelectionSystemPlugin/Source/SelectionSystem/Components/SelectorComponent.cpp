// © 2024 John Henry Miller. All rights reserved

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
	
	DOREPLIFETIME_CONDITION_NOTIFY(USelectorComponent, SelectedComponents, COND_None, REPNOTIFY_Always);

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

	const TArray<USelectableComponent*> OldSelectedComponents = SelectedComponents;
	
	SelectedComponents.AddUnique(SelectableComponent);
	
	OnRep_SelectedComponents(OldSelectedComponents);
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

	const TArray<USelectableComponent*> OldSelectedComponents = SelectedComponents;

	SelectedComponents.Remove(SelectableComponent);
	
	OnRep_SelectedComponents(OldSelectedComponents);
}

void USelectorComponent::ClearSelection(bool bRepToServer)
{
	if (bRepToServer && !GetOwner()->HasAuthority())
	{
		ServerClearSelection();
	}
	
	const TArray<USelectableComponent*> OldSelectedComponents = SelectedComponents;

	SelectedComponents.Empty();
	
	OnRep_SelectedComponents(OldSelectedComponents);
}

void USelectorComponent::OnRep_SelectedComponents(const TArray<USelectableComponent*>& OldSelectedComponents)
{
	for (USelectableComponent* OldSelectedComponent : OldSelectedComponents)
	{
		if (OldSelectedComponent && !SelectedComponents.Contains(OldSelectedComponent))
		{
			OldSelectedComponent->OnDeselected(GetOwner());
		}
	}

	for (USelectableComponent* SelectedComponent : SelectedComponents)
	{
		if (SelectedComponent && !OldSelectedComponents.Contains(SelectedComponent))
		{
			SelectedComponent->OnSelected(GetOwner());
		}
	}
}

void USelectorComponent::ServerSelect_Implementation(USelectableComponent* SelectableComponent)
{
	Select(SelectableComponent);
}

void USelectorComponent::ServerDeselect_Implementation(USelectableComponent* SelectableComponent)
{
	Deselect(SelectableComponent);
}

void USelectorComponent::ServerClearSelection_Implementation()
{
	ClearSelection();
}

#pragma endregion