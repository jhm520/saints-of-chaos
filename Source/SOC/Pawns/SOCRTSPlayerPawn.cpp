// © 2024 John Henry Miller. All rights reserved

#include "SOCRTSPlayerPawn.h"
#include "SelectionSystem/Components/SelectorComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilityCollection.h"
#include "SOCAI/SOCAIFunctionLibrary.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "CommandSystem/Components/CommandComponent.h"
#include "MinimapSystem/Components/MinimapViewComponent.h"

#pragma region Framework

// Sets default values for this pawn's properties
ASOCRTSPlayerPawn::ASOCRTSPlayerPawn()
{
	SetReplicates(true);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	SelectorComponent = CreateDefaultSubobject<USelectorComponent>(TEXT("SelectorComponent"));

	CommandComponent = CreateDefaultSubobject<UCommandComponent>(TEXT("CommandComponent"));

	MinimapViewComponent = CreateDefaultSubobject<UMinimapViewComponent>(TEXT("MinimapViewComponent"));
}

// Called when the game starts or when spawned
void ASOCRTSPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASOCRTSPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASOCRTSPlayerPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystem();
	
	
}

void ASOCRTSPlayerPawn::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilitySystem();
}



#pragma endregion

#pragma region Gameplay Abilities

UAbilitySystemComponent* ASOCRTSPlayerPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASOCRTSPlayerPawn::InitAbilitySystem()
{
	if(!AbilitySystemComponent)
	{
		return;
	}
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

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

#pragma endregion

#pragma region Attitude System

EAttitude ASOCRTSPlayerPawn::GetAttitudeTowards_Implementation(AActor* Other) const
{
	const bool bIsDirectedByMe = USOCAIFunctionLibrary::IsActorDirectedBy(Other, this);

	if (bIsDirectedByMe)
	{
		return EAttitude::Friendly;
	}

	return EAttitude::Hostile;
}

#pragma endregion