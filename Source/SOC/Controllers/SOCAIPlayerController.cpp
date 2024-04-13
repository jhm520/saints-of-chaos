// © 2024 John Henry Miller. All rights reserved


#include "SOCAIPlayerController.h"


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