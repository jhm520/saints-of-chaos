// © 2024 John Henry Miller. All rights reserved


#include "SOCAIPlayerController.h"
#include "GameFramework/PlayerState.h"


#pragma region Framework

ASOCAIPlayerController::ASOCAIPlayerController()
{
	AutoOwnershipComponent = CreateDefaultSubobject<UAutoOwnershipComponent>(TEXT("AutoOwnershipComponent"));

}

#pragma endregion

#pragma region Auto Ownership

UAutoOwnershipComponent* ASOCAIPlayerController::GetAutoOwnershipComponent() const
{
	return AutoOwnershipComponent;
}

#pragma endregion

#pragma region Objective System

UObjectiveAssigneeComponent* ASOCAIPlayerController::GetObjectiveAssigneeComponent() const
{
	const APlayerState* LocalPlayerState = GetPlayerState<APlayerState>();

	if (!LocalPlayerState)
	{
		return nullptr;
	}

	const IObjectiveAssigneeInterface* AssigneeInterface = Cast<IObjectiveAssigneeInterface>(LocalPlayerState);

	if (!AssigneeInterface)
	{
		return nullptr;
	}

	return AssigneeInterface->GetObjectiveAssigneeComponent();
}

AActor* ASOCAIPlayerController::GetAssignee()
{
	APlayerState* LocalPlayerState = GetPlayerState<APlayerState>();

	if (!LocalPlayerState)
	{
		return nullptr;
	}

	IObjectiveAssigneeInterface* AssigneeInterface = Cast<IObjectiveAssigneeInterface>(LocalPlayerState);

	if (!AssigneeInterface)
	{
		return nullptr;
	}

	return AssigneeInterface->GetAssignee();
}


#pragma endregion