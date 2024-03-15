// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCPlayerController.h"

#include "AbilitySystemComponent.h"
#include "EngineUtils.h"
#include "CoreUtility/Clicking/Components/ClickingComponent.h"
#include "GameFramework/GameMode.h"
#include "SOC/Gameplay/Buildings/Building.h"
#include "SOCAI/SOCAIFunctionLibrary.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "GameFramework/PlayerState.h"
#include "SOC/Gameplay/Buildings/BuildingSubsystem.h"

static TAutoConsoleVariable<bool> CVarEnableGameDebugCommands(
	TEXT("Game.EnableDebugCommands"),
	!UE_BUILD_SHIPPING, // Only enable it for non-shipping builds
	TEXT("Enables debug commands. (Server only)")
);

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
	if (!CVarEnableGameDebugCommands->GetBool())
	{
		return;
	}
	
	DebugSpawnMobs();
}

// Sets default values for this character's properties
void ASOCPlayerController::DebugStartSpawningMobs()
{
	if (!HasAuthority())
	{
		Server_DebugStartSpawningMobs();
		return;
	}

	UBuildingSubsystem* BuildingSubsystem = GetWorld()->GetSubsystem<UBuildingSubsystem>();

	if (!BuildingSubsystem)
	{
		return;
	}

	for (ASOCBuilding* Building : BuildingSubsystem->GetAllBuildings())
	{
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

		AbilitySystemComponent->TryActivateAbilityByClass(Building->MobSpawnAbilityClass, true);
	}
}

void ASOCPlayerController::Server_DebugStartSpawningMobs_Implementation()
{
	if (!CVarEnableGameDebugCommands->GetBool())
	{
		return;
	}
	
	DebugStartSpawningMobs();
}

// Sets default values for this character's properties
void ASOCPlayerController::DebugStopSpawningMobs()
{
	if (!HasAuthority())
	{
		Server_DebugStopSpawningMobs();
		return;
	}

	UBuildingSubsystem* BuildingSubsystem = GetWorld()->GetSubsystem<UBuildingSubsystem>();

	if (!BuildingSubsystem)
	{
		return;
	}

	for (ASOCBuilding* Building : BuildingSubsystem->GetAllBuildings())
	{
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
		

		FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(Building->MobSpawnAbilityClass);

		if (!AbilitySpec)
		{
			continue;
		}

		AbilitySystemComponent->CancelAbility(AbilitySpec->Ability);
	}
}

void ASOCPlayerController::Server_DebugStopSpawningMobs_Implementation()
{
	if (!CVarEnableGameDebugCommands->GetBool())
	{
		return;
	}
	
	DebugStopSpawningMobs();
}

// Starts the game match
void ASOCPlayerController::DebugStartMatch()
{
	if (!HasAuthority())
	{
		Server_DebugStartMatch();
		return;
	}

	AGameMode* GameMode = Cast<AGameMode>(GetWorld()->GetAuthGameMode());

	if (!GameMode)
	{
		return;
	}

	GameMode->StartMatch();
}

void ASOCPlayerController::Server_DebugStartMatch_Implementation()
{
	if (!CVarEnableGameDebugCommands->GetBool())
	{
		return;
	}

	DebugStartMatch();
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

	const bool bIsDirectedByMe = USOCAIFunctionLibrary::IsActorDirectedBy(Other, this);

	if (bIsDirectedByMe)
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

#pragma region Clicking

UClickingComponent* ASOCPlayerController::GetClickingComponent() const
{
	return ClickingComponent;
}

#pragma endregion

#pragma region Objective System

UObjectiveAssigneeComponent* ASOCPlayerController::GetObjectiveAssigneeComponent() const
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

AActor* ASOCPlayerController::GetAssignee()
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

