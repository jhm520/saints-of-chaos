// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "SOCCharacter.generated.h"

/**
 * 
 */
//Base class for characters
class UGameplayAbilityCollection;
UCLASS()
class SOC_API ASOCCharacter : public ACharacter, public IAbilitySystemInterface
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
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	UFUNCTION()
	void InitAbilitySystem();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TObjectPtr<UGameplayAbilityCollection>> AbilityCollections;
#pragma endregion 
	
};
