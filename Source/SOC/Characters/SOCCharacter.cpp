// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilityCollection.h"
#include "SOCAI/SOCAIGameplayTags.h"

ASOCCharacter::ASOCCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
}

void ASOCCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitAbilitySystem();
}

void ASOCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetupGameplayTags();

}

void ASOCCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASOCCharacter::SetupGameplayTags()
{
	// const TArray<FGameplayTag> FindEnemy = {
	// 	SOCAIBehaviorTags::FindEnemy,
	// 	SOCAIBehaviorTags::CallForBackup,
	// 	SOCAIBehaviorTags::MoveToAllies,
	// 	SOCAIBehaviorTags::RaiseAlarm,
	// 	SOCAIBehaviorTags::EngageEnemy,
	// 	SOCAIBehaviorTags::MoveToCombatRange,
	// 	SOCAIBehaviorTags::CallForBackup,
	// 	SOCAIBehaviorTags::CallForBackup,
	// 	SOCAIBehaviorTags::CallForBackup,
	// 	SOCAIBehaviorTags::CallForBackup,
	//
	// };
	// FGameplayTagContainer FindEnemyContainer = FGameplayTagContainer::CreateFromArray(GameplayTagArray);
}

#pragma region Gameplay Abilities

void ASOCCharacter::InitAbilitySystem()
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

UAbilitySystemComponent* ASOCCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
#pragma endregion
