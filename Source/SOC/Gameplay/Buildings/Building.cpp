// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"	
#include "BuildingSubsystem.h"
#include "GameplayAbilityCollection.h"
#include "GameplayAbilitySpecHandle.h"
#include "GASUtilityHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

#pragma region Framework
// Sets default values
ASOCBuilding::ASOCBuilding()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	OwningControllerId = -1;
}

// Called when the game starts or when spawned
void ASOCBuilding::BeginPlay()
{
	UBuildingSubsystem* BuildingSubsystem = UBuildingSubsystem::Get(this);

	if (BuildingSubsystem)
	{
		BuildingSubsystem->Register(this);
	}
	
	Super::BeginPlay();
}

void ASOCBuilding::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopSpawningMobs();

	UBuildingSubsystem* BuildingSubsystem = UBuildingSubsystem::Get(this);

	if (BuildingSubsystem)
	{
		BuildingSubsystem->Unregister(this);
	}
	
	Super::EndPlay(EndPlayReason);
}


void ASOCBuilding::SetOwner( AActor* NewOwner )
{
	Super::SetOwner(NewOwner);

	if (NewOwner)
	{
		InitAbilitySystem();

		StartSpawningMobs();
	}
}

void ASOCBuilding::OnRep_Owner()
{
	Super::OnRep_Owner();
	
	InitAbilitySystem();

}


// Called every frame
void ASOCBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASOCBuilding::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

#pragma endregion

 #pragma region Gameplay Abilities

void ASOCBuilding::InitAbilitySystem()
{
	if(!AbilitySystemComponent)
	{
		return;
	}
	
	AbilitySystemComponent->InitAbilityActorInfo(GetOwner(), this);

	//go through each ability collection and add it to this character's abilities
	TArray<FGameplayAbilitySpecHandle> BoundHandles;
	TArray<FGameplayAbilitySpecHandle> DefaultBoundHandles;
	
	for (TObjectPtr<UGameplayAbilityCollection> Collection : AbilityCollections)
	{
		if (!IsValid(Collection))
		{
			continue;
		}

		Collection->GiveAbilities(AbilitySystemComponent, BoundHandles, DefaultBoundHandles);
	}
}

UAbilitySystemComponent* ASOCBuilding::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
#pragma endregion

#pragma region Spawn Mob

void ASOCBuilding::StartSpawningMobs()
{
	if (!GetWorld())
	{
		return;
	}
	
	if (!AbilitySystemComponent)
	{
		return;
	}
	
	AbilitySystemComponent->TryActivateAbilityByClass(MobSpawnAbilityClass, true);
}

void ASOCBuilding::StopSpawningMobs()
{
	if (!GetWorld())
	{
		return;
	}
	
	if (!AbilitySystemComponent)
	{
		return;
	}

	FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(MobSpawnAbilityClass);

	if (!AbilitySpec)
	{
		return;
	}

	if (!AbilitySpec->Ability)
	{
		return;
	}

	
	AbilitySpec->Ability->CancelAbility(AbilitySpec->Ability->GetCurrentAbilitySpecHandle(), AbilitySpec->Ability->GetCurrentActorInfo(), AbilitySpec->Ability->GetCurrentActivationInfo(), true);
}

void ASOCBuilding::Timer_SpawnMob()
{
	if (!AbilitySystemComponent)
	{
		return;
	}
	
	AbilitySystemComponent->TryActivateAbilityByClass(MobSpawnAbilityClass, true);
}

#pragma endregion

#pragma region Auto Ownership
// Automatically takes ownership of designated actors at begin play
bool ASOCBuilding::CanTakeOwnership(AActor* InOwner) const
{
	if (!InOwner || !InOwner->HasAuthority())
	{
		return false;
	}
	
	if (OwningControllerId == -1)
	{
		return false;
	}

	APlayerController* PlayerController = Cast<APlayerController>(InOwner);
	
	if (!PlayerController)
	{
		return false;
	}

	AGameStateBase* GameStateBase = GetWorld()->GetGameState<AGameStateBase>();

	if (!GameStateBase)
	{
		return false;
	}

	TArray<APlayerState*> PlayerStates = GameStateBase->PlayerArray;

	APlayerState* OwningPlayerState = PlayerController->GetPlayerState<APlayerState>();

	if (!OwningPlayerState)
	{
		return false;
	}

	int32 PlayerIndex;
	
	bool bFoundPlayer = PlayerStates.Find(OwningPlayerState, PlayerIndex);

	if (!bFoundPlayer)
	{
		return false;
	}
	
	if (PlayerIndex != OwningControllerId)
	{
		return false;
	}
	
	return true;
}

#pragma endregion
