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

