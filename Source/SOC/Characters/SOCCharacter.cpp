// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilityCollection.h"
#include "SOCAI/SOCAIGameplayTags.h"
#include "SOC/Attributes/Health/HealthAttributeSet.h"
#include "AggroSystem/Components/AggroSystemComponent.h"

ASOCCharacter::ASOCCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AggroSystemComponent = CreateDefaultSubobject<UAggroSystemComponent>(TEXT("AggroSystemComponent"));

	HealthAttributeSet = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("HealthAttribute"));

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

	HealthAttributeSet->InitHealth(100.0f);
	HealthAttributeSet->InitMaxHealth(100.0f);
}

UAbilitySystemComponent* ASOCCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
#pragma endregion

#pragma region Aggro System
bool ASOCCharacter::ShouldAggro(AActor* AggroTarget) const
{
	const EAttitude AttitudeTowardTarget = IAttitudeInterface::Execute_GetAttitudeTowards(this, AggroTarget);

	return AttitudeTowardTarget == EAttitude::Hostile;
}

#pragma endregion

#pragma region Health Interface

float ASOCCharacter::GetHealth_Implementation() const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	if (!ASC)
	{
		return 0.0f;
	}

	if (!HealthAttributeSet)
	{
		return 0.0f;
	}

	return HealthAttributeSet->GetHealth();
}
void ASOCCharacter::SetHealth_Implementation(float NewHealth)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	if (!ASC)
	{
		return;
	}

	if (!HealthAttributeSet)
	{
		return;
	}

	return HealthAttributeSet->SetHealth(NewHealth);
}

float ASOCCharacter::GetMaxHealth_Implementation() const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	if (!ASC)
	{
		return 0.0f;
	}

	if (!HealthAttributeSet)
	{
		return 0.0f;
	}

	return HealthAttributeSet->GetMaxHealth();
}

void ASOCCharacter::SetMaxHealth_Implementation(float NewMaxHealth)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	if (!ASC)
	{
		return;
	}

	if (!HealthAttributeSet)
	{
		return;
	}

	return HealthAttributeSet->SetMaxHealth(NewMaxHealth);
}

bool ASOCCharacter::IsAlive_Implementation() const
{
	return IHealthInterface::Execute_GetHealth(this) > 0.0f;
}

void ASOCCharacter::OnHealthChanged_Implementation(float OldHealth, float NewHealth, float MaxHealth)
{
	if (HasAuthority() && NewHealth <= 0.0f && OldHealth > 0.0f)
	{
		Die();
	}
}

void ASOCCharacter::OnMaxHealthChanged_Implementation(float OldMaxHealth, float MaxHealth, float CurrentHealth)
{
	
}

#pragma endregion

#pragma region Death

void ASOCCharacter::Die()
{
	OnDeath();
}

void ASOCCharacter::OnDeath()
{
	K2_OnDeath();

	if (HasAuthority())
	{
		Destroy();
	}
}

#pragma endregion
