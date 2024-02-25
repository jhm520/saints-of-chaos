// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCPlayerController.h"

#include "AbilitySystemComponent.h"
#include "EngineUtils.h"
#include "CoreUtility/Clicking/Components/ClickingComponent.h"
#include "SOC/Gameplay/Buildings/Building.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"


#pragma region Framework

ASOCPlayerController::ASOCPlayerController()
{
	AutoOwnershipComponent = CreateDefaultSubobject<UAutoOwnershipComponent>(TEXT("AutoOwnershipComponent"));

	ClickingComponent = CreateDefaultSubobject<UClickingComponent>(TEXT("ClickingComponent"));
}

#pragma endregion

#pragma region Debug

void ASOCPlayerController::DebugSpawnMobs()
{
	if (!HasAuthority())
	{
		Server_DebugSpawnMobs();
		return;
	}
	
	for (TActorIterator<ASOCBuilding> It(GetWorld()); It; ++It)
	{
		ASOCBuilding* Building = *It;

		if (!Building)
		{
			continue;
		}

		IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Building);

		if (!AbilitySystemInterface)
		{
			continue;
		}

		UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();

		if (!AbilitySystemComponent)
		{
			continue;
		}

		AbilitySystemComponent->TryActivateAbilityByClass(MobSpawnAbilityClass, true);
	}
}

void ASOCPlayerController::Server_DebugSpawnMobs_Implementation()
{
	DebugSpawnMobs();
}

#pragma endregion

#pragma region Gameplay Abilities
UAbilitySystemComponent* ASOCPlayerController::GetAbilitySystemComponent() const
{
	if (!GetPawn())
	{
		return nullptr;
	}

	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(GetPawn());

	if (!AbilitySystemInterface)
	{
		return nullptr;
	}

	return AbilitySystemInterface->GetAbilitySystemComponent();
}

#pragma endregion

#pragma region Attitude

EAttitude ASOCPlayerController::GetAttitudeTowards_Implementation(AActor* Other) const
{
	if (GetPawn() && GetPawn()->Implements<UAttitudeInterface>())
	{
		return IAttitudeInterface::Execute_GetAttitudeTowards(GetPawn(), Other);
	}
	
	return EAttitude::Neutral;
}

#pragma endregion

#pragma region Selection System

USelectorComponent* ASOCPlayerController::GetSelectorComponent() const
{
	ISelectorInterface* SelectorInterface = Cast<ISelectorInterface>(GetPawn());

	if (!SelectorInterface)
	{
		return nullptr;
	}

	return SelectorInterface->GetSelectorComponent();
}

#pragma endregion

#pragma region Clicking

UClickingComponent* ASOCPlayerController::GetClickingComponent() const
{
	return ClickingComponent;
}

#pragma endregion
