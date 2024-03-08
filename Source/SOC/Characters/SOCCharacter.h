// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AggroSystem/Components/AggroSystemComponent.h"
#include "AggroSystem/Interfaces/AggroInterface.h"
#include "CoreUtility/Attitude/AttitudeInterface.h"
#include "CoreUtility/Clicking/Interfaces/ClickableActorInterface.h"
#include "SOC/Attributes/Health/HealthInterface.h"
#include "SelectionSystem/Interfaces/SelectableInterface.h"
#include "GameplayTagContainer.h"
#include "SOCCharacter.generated.h"

/**
 * 
 */
//Base class for characters
class UGameplayAbilityCollection;
class UAggroSytemComponent;
class UHealthAttributeSet;
class UWidgetComponent;
class UCharacterInfoWidget;
class USelectableComponent;

UCLASS()
class SOC_API ASOCCharacter : public ACharacter, public IAbilitySystemInterface, public IAttitudeInterface,
public IAggroInterface, public IHealthInterface, public ISelectableInterface, public IClickableActorInterface
{
	GENERATED_BODY()
#pragma region Framework
protected:
	ASOCCharacter();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(const float DeltaSeconds) override;

public:
	virtual void PossessedBy(AController* NewController) override;
#pragma endregion
public:
	void SetupGameplayTags();

#pragma region Gameplay Abilities
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	UFUNCTION()
	void InitAbilitySystem();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TObjectPtr<UGameplayAbilityCollection>> AbilityCollections;
#pragma endregion

#pragma region Attribute: Health
protected:
	UPROPERTY()
	TObjectPtr<UHealthAttributeSet> HealthAttributeSet;
#pragma endregion

#pragma region Aggro System
public:
	virtual UAggroSystemComponent* GetAggroSystemComponent() const override { return AggroSystemComponent;};

	virtual bool ShouldAggro(AActor* AggroTarget) const override;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAggroSystemComponent> AggroSystemComponent;
#pragma endregion

#pragma region Attitude System
	virtual EAttitude GetAttitudeTowards_Implementation(AActor* Other) const override;

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
	virtual void Die();

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

#pragma region Selection System

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Selection")
	TObjectPtr<USelectableComponent> SelectableComponent;

public:

	virtual USelectableComponent* GetSelectableComponent() const override {return SelectableComponent;};

#pragma endregion
	
#pragma region Clickable Actor Interface
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Selection")
	TObjectPtr<UClickableActorComponent> ClickableActorComponent;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Selection")
	TObjectPtr<UCapsuleComponent> ClickableCapsuleComponent;
	
	virtual UPrimitiveComponent* GetClickableComponent() const override;

	virtual UClickableActorComponent* GetClickableActorComponent() const override {return ClickableActorComponent;};

#pragma endregion

};
