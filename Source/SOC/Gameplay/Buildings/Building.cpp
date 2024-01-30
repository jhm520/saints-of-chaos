// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"	
#include "GameplayAbilityCollection.h"
#include "GameplayAbilitySpecHandle.h"
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
	Super::BeginPlay();
	
}

void ASOCBuilding::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopSpawningMobs();
	
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

	Timer_SpawnMob();
	
	FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(MobSpawnAbilityClass);

	if (!AbilitySpec)
	{
		return;
	}

	if (!AbilitySpec->Ability)
	{
		return;
	}

	UGameplayEffect* GameplayEffect = AbilitySpec->Ability->GetCooldownGameplayEffect();

	if (!GameplayEffect)
	{
		return;
	}

	float TimeRemaining;
	float Duration;
	FGameplayTagContainer TagContainer;
	GameplayEffect->GetOwnedGameplayTags(TagContainer);
	
	GetCooldownRemainingForTag(AbilitySystemComponent, TagContainer, TimeRemaining, Duration);
	
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnMob, this, &ASOCBuilding::Timer_SpawnMob, TimeRemaining, true);
}

bool ASOCBuilding::GetCooldownRemainingForTag(UAbilitySystemComponent* Target, FGameplayTagContainer InCooldownTags, float& TimeRemaining,
															float& CooldownDuration)
{
	if (IsValid(Target) && InCooldownTags.Num() > 0)
	{
		TimeRemaining = 0.f;
		CooldownDuration = 0.f;

		FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTags);
		TArray<TPair<float, float>> DurationAndTimeRemaining = Target->GetActiveEffectsTimeRemainingAndDuration(Query);
		if (DurationAndTimeRemaining.Num() > 0)
		{
			int32 BestIdx = 0;
			float LongestTime = DurationAndTimeRemaining[0].Key;
			for (int32 Idx = 1; Idx < DurationAndTimeRemaining.Num(); ++Idx)
			{
				if (DurationAndTimeRemaining[Idx].Key > LongestTime)
				{
					LongestTime = DurationAndTimeRemaining[Idx].Key;
					BestIdx = Idx;
				}
			}

			TimeRemaining = DurationAndTimeRemaining[BestIdx].Key;
			CooldownDuration = DurationAndTimeRemaining[BestIdx].Value;

			return true;
		}
	}

	return false;
}

void ASOCBuilding::StopSpawningMobs()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_SpawnMob);
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

