// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"	
#include "BuildingSubsystem.h"
#include "GameplayAbilityCollection.h"
#include "GameplayAbilitySpecHandle.h"
#include "GASUtilityHelperLibrary.h"
#include "CoreUtility/CoreUtilityBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "SOCAI/SOCAIFunctionLibrary.h"
#include "SOCAI/Components/SOCAIAvatarComponent.h"
#include "SOCAI/Components/SOCAIBehaviorComponent.h"

#pragma region Framework
// Sets default values
ASOCBuilding::ASOCBuilding()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	OwningControllerId = -1;

	BehaviorComponent = CreateDefaultSubobject<USOCAIBehaviorComponent>(TEXT("BehaviorComponent"));
	AvatarComponent = CreateDefaultSubobject<USOCAIAvatarComponent>(TEXT("AvatarComponent"));
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
		
		AController* ControllerDirector = Cast<AController>(NewOwner);

		if (!ControllerDirector)
		{
			return;
		}
		
		ControllerDirector->OnPossessedPawnChanged.AddDynamic(this, &ASOCBuilding::OnDirectorPossessedPawnChanged);
	
		BehaviorComponent->InitBehaviorSystem(ControllerDirector, ControllerDirector->GetPawn());
	}
}

void ASOCBuilding::OnRep_Owner()
{
	Super::OnRep_Owner();
	
	InitAbilitySystem();

	AController* ControllerDirector = Cast<AController>(GetOwner());

	if (!ControllerDirector)
	{
		return;
	}
	
	BehaviorComponent->InitBehaviorSystem(ControllerDirector, ControllerDirector->GetPawn());
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

	if (!AbilitySpec->Ability->CanBeCanceled())
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

	const int32 ControllerId = UCoreUtilityBlueprintLibrary::GetAuthPlayerControllerId(this, PlayerController);
	
	if (ControllerId != OwningControllerId)
	{
		return false;
	}
	
	return true;
}

#pragma endregion

#pragma region Attitude

EAttitude ASOCBuilding::GetAttitudeTowards_Implementation(AActor* Other) const
{
	if (!Other)
	{
		return EAttitude::Neutral;
	}

	if (!GetAvatarComponent())
	{
		return EAttitude::Neutral;
	}

	APawn* DirectorPawn = GetAvatarComponent()->GetDirectorPawn();

	if (!DirectorPawn)
	{
		return EAttitude::Neutral;
	}

	const bool bIsDirectedByMyDirector = USOCAIFunctionLibrary::IsActorDirectedBy(Other, DirectorPawn);

	if (bIsDirectedByMyDirector)
	{
		return EAttitude::Friendly;
	}

	return EAttitude::Hostile;
}

#pragma endregion

#pragma region Behavior

void ASOCBuilding::OnDirectorPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	AController* ControllerDirector = Cast<AController>(GetBehaviorComponent()->GetDirector());

	if (!ControllerDirector)
	{
		return;
	}
	
	BehaviorComponent->InitBehaviorSystem(ControllerDirector, ControllerDirector->GetPawn());
}

#pragma endregion