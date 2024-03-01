// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandInfo.h"

#include "CommandSubsystem.h"
#include "Components/CommandableComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/CommandableInterface.h"

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
	OnBegin_AnimInstances(Commandable, Command);
}

void UCommandInfo::OnCommandFinished(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	OnComplete_AnimInstances(Commandable, Command);
}

bool UCommandInfo::CheckCommandFinished(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	return false;
}

#pragma endregion

#pragma region Animation
void UCommandInfo::OnBegin_AnimInstances(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	if (!Commandable)
	{
		return;
	}
	
	const ACharacter* AvatarCharacter = Cast<ACharacter>(Commandable->GetOwner());

	if (!AvatarCharacter)
	{
		return;
	}
	
	for (const FCommandAnimInstance& LocalAnimInstance : CommandAnimInstances)
	{
		if (LocalAnimInstance.ActivationMode == ECommandTriggerMode::OnBegin)
		{
			AvatarCharacter->GetMesh()->GetAnimInstance()->LinkAnimClassLayers(LocalAnimInstance.AnimInstanceClass);
		}

		if (LocalAnimInstance.DeactivationMode == ECommandTriggerMode::OnBegin)
		{
			AvatarCharacter->GetMesh()->GetAnimInstance()->UnlinkAnimClassLayers(LocalAnimInstance.AnimInstanceClass);
		}
	}
}

void UCommandInfo::OnComplete_AnimInstances(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	if (!Commandable)
	{
		return;
	}
	
	const ACharacter* AvatarCharacter = Cast<ACharacter>(Commandable->GetOwner());

	if (!AvatarCharacter)
	{
		return;
	}
	
	for (const FCommandAnimInstance& LocalAnimInstance : CommandAnimInstances)
	{
		if (LocalAnimInstance.ActivationMode == ECommandTriggerMode::OnComplete)
		{
			AvatarCharacter->GetMesh()->GetAnimInstance()->LinkAnimClassLayers(LocalAnimInstance.AnimInstanceClass);
		}

		if (LocalAnimInstance.DeactivationMode == ECommandTriggerMode::OnComplete)
		{
			AvatarCharacter->GetMesh()->GetAnimInstance()->UnlinkAnimClassLayers(LocalAnimInstance.AnimInstanceClass);
		}
	}
}

#pragma endregion