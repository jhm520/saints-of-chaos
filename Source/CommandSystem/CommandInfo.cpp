// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandInfo.h"

#include "CommandSubsystem.h"
#include "Components/CommandableComponent.h"

#pragma region Framework

void UCommandInfo::PostLoad()
{
	Super::PostLoad();
}

void UCommandInfo::PostInitProperties()
{
	Super::PostInitProperties();
}


void UCommandInfo::BeginDestroy()
{
	Super::BeginDestroy();
}

#pragma endregion

#pragma region Command

bool UCommandInfo::CheckCommandFinished(UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	return K2_CheckCommandFinished(Commandable, Command);
}

#pragma endregion