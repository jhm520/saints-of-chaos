// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCRTSPlayerPawn.h"
#include "SelectionSystem/Components/SelectorComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilityCollection.h"
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
	if (!Other)
	{
		return EAttitude::Neutral;
	}

	ISOCAIBehaviorInterface* OtherBehaviorInterface = Cast<ISOCAIBehaviorInterface>(Other);

	if (!OtherBehaviorInterface)
	{
		return EAttitude::Neutral;
	}

	USOCAIAvatarComponent* AvatarComponent = OtherBehaviorInterface->GetAvatarComponent();

	if (!AvatarComponent)
	{
		return EAttitude::Neutral;
	}

	APawn* OtherDirectorPawn = AvatarComponent->GetDirectorPawn();

	if (!OtherDirectorPawn)
	{
		return EAttitude::Neutral;
	}

	if (this != OtherDirectorPawn)
	{
		return EAttitude::Hostile;
	}

	return EAttitude::Friendly;
}

#pragma endregion