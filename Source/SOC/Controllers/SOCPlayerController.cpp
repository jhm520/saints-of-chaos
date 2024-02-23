// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCPlayerController.h"

#include "AbilitySystemComponent.h"
#include "EngineUtils.h"

#include "SOC/Gameplay/Buildings/Building.h"


#pragma region Framework

ASOCPlayerController::ASOCPlayerController()
{
	AutoOwnershipComponent = CreateDefaultSubobject<UAutoOwnershipComponent>(TEXT("AutoOwnershipComponent"));
	
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
	//if its null, it's neutral
	if (!Other)
	{
		return EAttitude::Neutral;
	}
	
	AActor* OtherOwner = Other->GetOwner();

	//if it doesn't have an owner, it's neutral
	if (!OtherOwner)
	{
		return EAttitude::Neutral;
	}

	//follow the chain of ownership up to the top
	while (OtherOwner->GetOwner())
	{
		OtherOwner = OtherOwner->GetOwner();
	}

	if (OtherOwner == this)
	{
		return EAttitude::Friendly;
	}

	return EAttitude::Hostile;
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
