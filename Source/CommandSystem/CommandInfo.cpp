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

void UCommandInfo::OnCommandBegin(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	
}


bool UCommandInfo::CheckCommandFinished(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	return false;
}

#pragma endregion