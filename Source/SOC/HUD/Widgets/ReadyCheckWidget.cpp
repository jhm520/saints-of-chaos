// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadyCheckWidget.h"

#include "ObjectiveSystem/ObjectiveSystemBlueprintLibrary.h"
#include "ObjectiveSystem/Interfaces/ObjectiveAssigneeInterface.h"

#pragma region Ready Check
void UReadyCheckWidget::OnSetReady(bool bIsReady)
{
	IObjectiveAssigneeInterface* ObjectiveAssigneeInterface = Cast<IObjectiveAssigneeInterface>(GetOwningPlayer());

	if (!ObjectiveAssigneeInterface)
	{
		return;
	}

	//get the actor that represents the player as an objective assignee
	AActor* Assignee = ObjectiveAssigneeInterface->GetAssignee();

	if (!Assignee)
	{
		return;
	}

	//progress or regress objectives for the assignee if we check or uncheck the ready check
	UObjectiveSystemBlueprintLibrary::ProgressObjectivesForAssigneeByTags(Assignee, ReadyCheckTags, bIsReady);
}
#pragma endregion