// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"	
#include "BuildingSubsystem.h"
#include "GameplayAbilityCollection.h"
#include "GameplayAbilitySpecHandle.h"
#include "GASUtilityHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "CoreUtility/CoreUtilityBlueprintLibrary.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "SOC/Attributes/Health/HealthAttributeSet.h"
#include "SOC/HUD/Widgets/CharacterInfoWidget.h"
#include "SOCAI/SOCAIFunctionLibrary.h"
#include "SOCAI/Components/SOCAIBehaviorComponent.h"

#pragma region Framework
// Sets default values
ASOCBuilding::ASOCBuilding()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetCapsuleRadius(50.0f);
	CapsuleComponent->SetCapsuleHalfHeight(100.0f);
	
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	OwningControllerId = -1;

	BehaviorComponent = CreateDefaultSubobject<USOCAIBehaviorComponent>(TEXT("BehaviorComponent"));
	HealthAttributeSet = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("HealthAttribute"));

	CharacterInfoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("CharacterInfoWidgetComponent"));
	CharacterInfoWidgetComponent->SetupAttachment(GetRootComponent());
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

	InitializeCharacterInfoWidget();
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
		
		BindGameModeEvents();
		
		AController* ControllerDirector = Cast<AController>(NewOwner);

		if (!ControllerDirector)
		{
			return;
		}
		
		ControllerDirector->OnPossessedPawnChanged.AddDynamic(this, &ASOCBuilding::OnDirectorPossessedPawnChanged);
	
		BehaviorComponent->InitBehaviorSystem(ControllerDirector->GetPawn());
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
	
	BehaviorComponent->InitBehaviorSystem(ControllerDirector->GetPawn());
}

// Called every frame
void ASOCBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickCharacterInfoWidgetOrientation();

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

	AActor* Director = GetBehaviorComponent()->GetDirector();

	if (!Director)
	{
		return EAttitude::Neutral;
	}

	const bool bIsDirectedByMyDirector = USOCAIFunctionLibrary::IsActorDirectedBy(Other, Director);

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
	BehaviorComponent->InitBehaviorSystem(NewPawn);
}

#pragma endregion

#pragma region Health Interface

float ASOCBuilding::GetHealth_Implementation() const
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
void ASOCBuilding::SetHealth_Implementation(float NewHealth)
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

float ASOCBuilding::GetMaxHealth_Implementation() const
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

void ASOCBuilding::SetMaxHealth_Implementation(float NewMaxHealth)
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

bool ASOCBuilding::IsAlive_Implementation() const
{
	return IHealthInterface::Execute_GetHealth(this) > 0.0f;
}

void ASOCBuilding::OnHealthChanged_Implementation(float OldHealth, float NewHealth, float MaxHealth)
{
	UpdateCharacterInfoWidget_Health();

	if (HasAuthority())
	{
		if (NewHealth <= 0.0f && OldHealth > 0.0f)
		{
			Die();
		}
	}
}

void ASOCBuilding::OnMaxHealthChanged_Implementation(float OldMaxHealth, float MaxHealth, float CurrentHealth)
{
	
}

#pragma endregion

#pragma region Death

void ASOCBuilding::Die()
{
	OnDeath();
}

void ASOCBuilding::OnDeath()
{
	K2_OnDeath();

	if (HasAuthority())
	{
		Destroy();
	}
}

#pragma endregion

#pragma region Character Info Widget

void ASOCBuilding::InitializeCharacterInfoWidget()
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

void ASOCBuilding::UpdateCharacterInfoWidget()
{
	InitializeCharacterInfoWidget();

	UpdateCharacterInfoWidget_Health();
	UpdateCharacterInfoWidget_Attitude();
}

void ASOCBuilding::TickCharacterInfoWidgetOrientation()
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


void ASOCBuilding::UpdateCharacterInfoWidget_Health()
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

void ASOCBuilding::UpdateCharacterInfoWidget_Attitude()
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

#pragma region GameMode
	
void ASOCBuilding::BindGameModeEvents()
{
	FGameModeEvents::OnGameModeMatchStateSetEvent().AddUObject(this, &ASOCBuilding::OnGameModeMatchStateSetEvent);
}

void ASOCBuilding::OnGameModeMatchStateSetEvent(FName NewMatchState)
{
	if (NewMatchState == NAME_None)
	{
		return;
	}

	if (NewMatchState == MatchState::InProgress)
	{
		StartSpawningMobs();
	}
}

#pragma endregion