// Fill out your copyright notice in the Description page of Project Settings.


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