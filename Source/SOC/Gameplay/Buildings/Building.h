// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "CoreUtility/AutoOwnership/Interfaces/AutoOwnershipInterface.h"
#include "GameFramework/Pawn.h"
#include "GameplayTagContainer.h"
#include "CoreUtility/Attitude/AttitudeInterface.h"
#include "CoreUtility/GameMode/Interfaces/CoreGameModeActorInterface.h"
#include "SOC/Attributes/Damage/DamageInterface.h"
#include "SOC/Attributes/Health/HealthInterface.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "Building.generated.h"

class UGameplayAbilityCollection;
class UAbilitySystemComponent;
class UHealthAttributeSet;
class UCharacterInfoWidget;
class UWidgetComponent;
class UCapsuleComponent;

UCLASS()
class SOC_API ASOCBuilding : public APawn, public IAbilitySystemInterface, public IAutoOwnershipInterface, public IAttitudeInterface, public ISOCAIBehaviorInterface, public IHealthInterface, public IDamageInterface, public ICoreGameModeActorInterface
{
	GENERATED_BODY()
#pragma region Framework
public:
	// Sets default values for this pawn's properties
	ASOCBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Called when owner changes, does nothing by default but can be overridden */
	virtual void OnRep_Owner() override;

	virtual void SetOwner( AActor* NewOwner ) override;

	virtual void Reset() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion

#pragma region Capsule

	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
#pragma endregion

#pragma region Spawn Mob

	UPROPERTY()
	FTimerHandle TimerHandle_SpawnMob;
	
	UFUNCTION()
	void StartSpawningMobs();

	UFUNCTION()
	void StopSpawningMobs();

	UFUNCTION()
	void Timer_SpawnMob();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug Commands")
	TSubclassOf<class UGameplayAbility> MobSpawnAbilityClass;

#pragma endregion

#pragma region Gameplay Ability System
public:
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	UFUNCTION()
	void InitAbilitySystem();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TObjectPtr<UGameplayAbilityCollection>> AbilityCollections;
#pragma endregion

#pragma region Auto Ownership
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Ownership")
	int32 OwningControllerId;
	
	// Automatically takes ownership of designated actors at begin play
	UFUNCTION()
	virtual bool CanTakeOwnership(AActor* InOwner) const override;

#pragma endregion

#pragma region Attitude

	EAttitude GetAttitudeTowards_Implementation(AActor* Other) const;

#pragma endregion

#pragma region Behavior

protected:
	UPROPERTY()
	TObjectPtr<USOCAIBehaviorComponent> BehaviorComponent;

public:

	virtual USOCAIBehaviorComponent* GetBehaviorComponent() const override {return BehaviorComponent;}
	
	virtual const AActor* GetAvatarActor() const override {return this;}

	UFUNCTION()
	void OnDirectorPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn);

#pragma endregion

#pragma region Attribute: Health
protected:
	UPROPERTY()
	TObjectPtr<UHealthAttributeSet> HealthAttributeSet;
#pragma endregion

#pragma region Health Interface

	virtual float GetHealth_Implementation() const override;
	virtual void SetHealth_Implementation(float NewHealth) override;
	virtual float GetMaxHealth_Implementation() const override;
	virtual void SetMaxHealth_Implementation(float NewMaxHealth) override;
	virtual bool IsAlive_Implementation() const override;
	virtual void OnHealthChanged_Implementation(float OldHealth, float NewHealth, float MaxHealth) override;
	virtual void OnMaxHealthChanged_Implementation(float OldMaxHealth, float MaxHealth, float CurrentHealth) override;

#pragma endregion

#pragma region Death

protected:
	virtual void Die(AActor* DamageCauser, AController* Killer);

	virtual void OnDeath();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="OnDeath", Category = "AI|Behavior")
	void K2_OnDeath();

#pragma endregion

#pragma region Character Info Widget

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Info")
	TSubclassOf<UCharacterInfoWidget> CharacterInfoWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Character Info")
	TObjectPtr<UCharacterInfoWidget> CharacterInfoWidget;

	void InitializeCharacterInfoWidget();
	
	void TickCharacterInfoWidgetOrientation();
	
	void UpdateCharacterInfoWidget();

	void UpdateCharacterInfoWidget_Health();
	void UpdateCharacterInfoWidget_Attitude();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Info")
	TObjectPtr<UWidgetComponent> CharacterInfoWidgetComponent;

#pragma endregion

#pragma region Game Mode
	
	void BindGameModeEvents();

	UFUNCTION()
	void OnGameModeMatchStateSetEvent(FName NewMatchState);

#pragma endregion

#pragma region Damage Interface
	
public:
	virtual void OnDamaged_Implementation(float Damage, float PreviousDamageTotal, AActor* DamageCauser, AController* InstigatorController) override;

#pragma endregion

#pragma region Core Game Mode Actor Interface

	virtual bool ShouldReset(AActor* Actor) const override;

#pragma endregion

};
