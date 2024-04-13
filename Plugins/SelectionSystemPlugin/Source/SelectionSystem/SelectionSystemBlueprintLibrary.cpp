// © 2024 John Henry Miller. All rights reserved

#include "SelectionSystemBlueprintLibrary.h"
#include "Interfaces/SelectableInterface.h"
#include "Interfaces/SelectorInterface.h"
#include "SelectionSystem/Components/SelectableComponent.h"
#include "SelectionSystem/Components/SelectorComponent.h"

void USelectionSystemBlueprintLibrary::SelectActor(AActor* Selector, const AActor* SelectedActor, bool bRepToServer)
{
	if (!Selector || !SelectedActor)
	{
		return;
	}

	ISelectorInterface* SelectorInterface = Cast<ISelectorInterface>(Selector);

	if (!SelectorInterface)
	{
		return;
	}

	USelectorComponent* SelectorComponent = SelectorInterface->GetSelectorComponent();

	if (!SelectorComponent)
	{
		return;
	}

	const ISelectableInterface* SelectedInterface = Cast<ISelectableInterface>(SelectedActor);

	if (!SelectedInterface)
	{
		return;
	}

	USelectableComponent* SelectableComponent = SelectedInterface->GetSelectableComponent();

	if (!SelectableComponent)
	{
		return;
	}
	
	//tell the selector component to select this character
	SelectorComponent->Select(SelectableComponent, bRepToServer);
}

void USelectionSystemBlueprintLibrary::SelectActors(AActor* Selector, const TArray<AActor*> SelectedActors, bool bRepToServer)
{
	for (AActor* SelectedActor : SelectedActors)
	{
		SelectActor(Selector, SelectedActor, bRepToServer);
	}
}
	

void USelectionSystemBlueprintLibrary::ClearSelection(AActor* Selector, bool bRepToServer)
{
	if (!Selector)
	{
		return;
	}

	ISelectorInterface* SelectorInterface = Cast<ISelectorInterface>(Selector);

	if (!SelectorInterface)
	{
		return;
	}

	USelectorComponent* SelectorComponent = SelectorInterface->GetSelectorComponent();

	if (!SelectorComponent)
	{
		return;
	}
	
	//tell the selector component to select this character
	SelectorComponent->ClearSelection(bRepToServer);
}

void USelectionSystemBlueprintLibrary::GetSelectedComponents(AActor* Selector, TArray<USelectableComponent*>& OutSelectedComponents)
{
	ISelectorInterface* SelectorInterface = Cast<ISelectorInterface>(Selector);

	if (!SelectorInterface)
	{
		return;
	}
	
	USelectorComponent* SelectorComponent = SelectorInterface->GetSelectorComponent();

	if (!SelectorComponent)
	{
		return;
	}

	//Get the selected units
	OutSelectedComponents = SelectorComponent->GetSelectedComponents();
}
