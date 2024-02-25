// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCRTSPlayerPawn.h"
#include "SelectionSystem/Components/SelectorComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilityCollection.h"
#include "SOCAI/SOCAIFunctionLibrary.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "SOCAI/Components/SOCAIAvatarComponent.h"

#pragma region Framework

// Sets default values for this pawn's properties
ASOCRTSPlayerPawn::ASOCRTSPlayerPawn()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	SelectorComponent = CreateDefaultSubobject<USelectorComponent>(TEXT("SelectorComponent"));
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