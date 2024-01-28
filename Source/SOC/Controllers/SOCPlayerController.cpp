// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCPlayerController.h"

#pragma region Framework

ASOCPlayerController::ASOCPlayerController()
{
	AutoOwnershipComponent = CreateDefaultSubobject<UAutoOwnershipComponent>(TEXT("AutoOwnershipComponent"));
	
}

#pragma endregion