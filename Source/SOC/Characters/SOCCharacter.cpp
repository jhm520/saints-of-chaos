// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilityCollection.h"
#include "GASUtilityHelperLibrary.h"
#include "SOCAI/SOCAIGameplayTags.h"
#include "SOC/Attributes/Health/HealthAttributeSet.h"
#include "AggroSystem/Components/AggroSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SOC/HUD/Widgets/CharacterInfoWidget.h"
#include "SelectionSystem/Components/SelectableComponent.h"
#include "Components/CapsuleComponent.h"
#include "SelectionSystem/Components/SelectorComponent.h"
#include "SelectionSystem/Interfaces/SelectorInterface.h"
#include "SOC/Abilities/SOCGameplayAbility_SelectActor.h"
#include "CoreUtility/Clicking/Components/ClickableActorComponent.h"
#include "Engine/DamageEvents.h"
#include "SOC/GameModes/SOCGameModeBase.h"

ASOCCharacter::ASOCCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	CharacterInfoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("CharacterInfoWidgetComponent"));
	CharacterInfoWidgetComponent->SetupAttachment(GetRootComponent());

	AggroSystemComponent = CreateDefaultSubobject<UAggroSystemComponent>(TEXT("AggroSystemComponent"));

	HealthAttributeSet = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("HealthAttribute"));

	SelectableComponent = CreateDefaultSubobject<USelectableComponent>(TEXT("SelectableComponent"));

	ClickableActorComponent = CreateDefaultSubobject<UClickableActorComponent>(TEXT("ClickableActorComponent"));

	ClickableCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ClickableCapsuleComponent"));
	ClickableCapsuleComponent->SetupAttachment(GetRootComponent());

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

	InitializeCharacterInfoWidget();
}

void ASOCCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASOCCharacter::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TickCharacterInfoWidgetOrientation();
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
	if (!AggroTarget || !AggroTarget->Implements<UAttitudeInterface>())
	{
		return false;
	}
	
	const EAttitude AttitudeTowardTarget = IAttitudeInterface::Execute_GetAttitudeTowards(this, AggroTarget);

	return AttitudeTowardTarget == EAttitude::Hostile;
}

#pragma endregion

#pragma region Attitude System
EAttitude ASOCCharacter::GetAttitudeTowards_Implementation(AActor* Other) const
{
	return EAttitude::Neutral;
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
	UpdateCharacterInfoWidget_Health();
}

void ASOCCharacter::OnMaxHealthChanged_Implementation(float OldMaxHealth, float MaxHealth, float CurrentHealth)
{
	
}

#pragma endregion

#pragma region Death

void ASOCCharacter::Die(AActor* DamageCauser, AController* Killer)
{
	ASOCGameModeBase* GameMode = Cast<ASOCGameModeBase>(GetWorld()->GetAuthGameMode());
	
	if (GameMode)
	{
		GameMode->OnActorKilled(this, DamageCauser, Killer);
	}
	
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

#pragma region Character Info Widget

void ASOCCharacter::InitializeCharacterInfoWidget()
{
	//if we already made this widget, don't make it again
	if (CharacterInfoWidget)
	{
		return;
	}

	if (!CharacterInfoWidgetClass)
	{
		return;
	}

	CharacterInfoWidget = CreateWidget<UCharacterInfoWidget>(GetWorld(), CharacterInfoWidgetClass);

	CharacterInfoWidgetComponent->SetWidget(CharacterInfoWidget);

	UpdateCharacterInfoWidget();
}

void ASOCCharacter::UpdateCharacterInfoWidget()
{
	InitializeCharacterInfoWidget();

	UpdateCharacterInfoWidget_Health();
	UpdateCharacterInfoWidget_Attitude();
}

void ASOCCharacter::TickCharacterInfoWidgetOrientation()
{
	if (!CharacterInfoWidgetComponent)
	{
		return;
	}
	
	APlayerController* LocalPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!LocalPC)
	{
		return;
	}
	
	const FVector& CameraLocation = LocalPC->PlayerCameraManager->GetCameraLocation();

	const FVector& ComponentLocation = CharacterInfoWidgetComponent->GetComponentLocation();
	
	CharacterInfoWidgetComponent->SetWorldRotation((CameraLocation - ComponentLocation).Rotation());
}


void ASOCCharacter::UpdateCharacterInfoWidget_Health()
{
	if (!CharacterInfoWidget)
	{
		InitializeCharacterInfoWidget();
		return;
	}

	const float CurrentHealth = IHealthInterface::Execute_GetHealth(this);
	const float MaxHealth = IHealthInterface::Execute_GetMaxHealth(this);
	
	CharacterInfoWidget->OnHealthChanged(CurrentHealth, MaxHealth);
}

void ASOCCharacter::UpdateCharacterInfoWidget_Attitude()
{
	if (!CharacterInfoWidget)
	{
		InitializeCharacterInfoWidget();
		return;
	}
	
	APlayerController* LocalPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!LocalPlayerController)
	{
		return;
	}

	const EAttitude Attitude = IAttitudeInterface::Execute_GetAttitudeTowards(LocalPlayerController, this);

	CharacterInfoWidget->UpdatePlayerAttitude(Attitude);
}

#pragma endregion

#pragma region Clickable Actor Interface

UPrimitiveComponent* ASOCCharacter::GetClickableComponent() const
{
	return ClickableCapsuleComponent;
}
#pragma endregion

#pragma region Damage Interface
	
void ASOCCharacter::OnDamaged_Implementation(float Damage, float PreviousDamageTotal, AActor* DamageCauser, AController* InstigatorController)
{
	TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), InstigatorController, DamageCauser);
	
	if (HasAuthority())
	{
		if (!IHealthInterface::Execute_IsAlive(this) && PreviousDamageTotal < IHealthInterface::Execute_GetMaxHealth(this))
		{
			Die(DamageCauser, InstigatorController);
		}
	}
}

#pragma endregion

#pragma region Damage Causer Interface
	
AController* ASOCCharacter::GetDamageInstigatorController() const
{
	return GetController();
}

#pragma endregion