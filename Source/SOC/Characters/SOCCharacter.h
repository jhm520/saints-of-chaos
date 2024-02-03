// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AggroSystem/Components/AggroSystemComponent.h"
#include "AggroSystem/Interfaces/AggroInterface.h"
#include "CoreUtility/Attitude/AttitudeInterface.h"
#include "SOCCharacter.generated.h"

/**
 * 
 */
//Base class for characters
class UGameplayAbilityCollection;
class UAggroSytemComponent;
class UHealthAttributeSet;
UCLASS()
class SOC_API ASOCCharacter : public ACharacter, public IAbilitySystemInterface, public IAttitudeInterface, public IAggroInterface
{
	GENERATED_BODY()
#pragma region Framework
protected:
	ASOCCharacter();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
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

};
