// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandInfo.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
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
	OnCommandBegin_GameplayAbilities(Commandable, Command);
}

void UCommandInfo::OnCommandFinished(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	OnComplete_AnimInstances(Commandable, Command);
	OnCommandFinished_GameplayAbilities(Commandable, Command);

}

void UCommandInfo::ContinueCommand(float DeltaSeconds, const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Red, TEXT("ContinueCommand") + Command.CommandInfo->GetName());
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

	if (!AvatarCharacter->GetMesh())
	{
		return;
	}

	if (!AvatarCharacter->GetMesh()->GetAnimInstance())
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

	
	if (!AvatarCharacter->GetMesh())
	{
		return;
	}

	if (!AvatarCharacter->GetMesh()->GetAnimInstance())
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

#pragma region Gameplay Ability System

void UCommandInfo::OnCommandBegin_GameplayAbilities(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	if (!Commandable)
	{
		return;
	}
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Commandable->GetOwner());

	for (const FCommandGameplayAbility& LocalAbility : CommandGameplayAbilities)
	{
		if (LocalAbility.ActivationMode == ECommandTriggerMode::OnBegin)
		{
			if (ASC)
			{
				ASC->TryActivateAbilityByClass(LocalAbility.GameplayAbilityClass, true);
			}
		}

		if (LocalAbility.DeactivationMode == ECommandTriggerMode::OnBegin)
		{
			if (ASC)
			{
				FGameplayAbilitySpec* AbilitySpec = ASC->FindAbilitySpecFromClass(LocalAbility.GameplayAbilityClass);

				if (AbilitySpec)
				{
					ASC->CancelAbility(AbilitySpec->Ability);
				}
			}
		}
	}
}

void UCommandInfo::OnCommandFinished_GameplayAbilities(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	if (!Commandable)
	{
		return;
	}
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Commandable->GetOwner());

	for (const FCommandGameplayAbility& LocalAbility : CommandGameplayAbilities)
	{
		if (LocalAbility.ActivationMode == ECommandTriggerMode::OnComplete)
		{
			if (ASC && LocalAbility.GameplayAbilityClass)
			{
				ASC->TryActivateAbilityByClass(LocalAbility.GameplayAbilityClass, true);
			}
		}

		if (LocalAbility.DeactivationMode == ECommandTriggerMode::OnComplete)
		{
			if (ASC)
			{
				FGameplayAbilitySpec* AbilitySpec = ASC->FindAbilitySpecFromClass(LocalAbility.GameplayAbilityClass);

				if (AbilitySpec && AbilitySpec->IsActive())
				{
					ASC->CancelAbility(AbilitySpec->Ability);
				}
			}
		}
	}
}

#pragma endregion