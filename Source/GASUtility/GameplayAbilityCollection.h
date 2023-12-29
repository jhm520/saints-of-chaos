// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/DataAsset.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityCollection.generated.h"


class UGameplayAbility;
// /**
//  *	Example struct that pairs a enum input command to a GameplayAbilityClass.6
//  */
UENUM(BlueprintType)
enum class EAbilityInputBindingKey : uint8
{
	Ability1 UMETA(DisplayName = "Ability1 (LMB)"),
	Ability2 UMETA(DisplayName = "Ability2 (RMB)"),
	Ability3 UMETA(DisplayName = "Ability3 (Q)"),
	Ability4 UMETA(DisplayName = "Ability4 (E)"),
	Ability5 UMETA(DisplayName = "Ability5 (R)"),
	Ability6 UMETA(DisplayName = "Ability6 (T)"),
	Ability7 UMETA(DisplayName = "Ability7 (Y)"),
	Ability8 UMETA(DisplayName = "Ability8 (U)"),
	Ability9 UMETA(DisplayName = "Ability9 (I)"),
	Ability10 UMETA(DisplayName = "Ability10 (O)"),
	Ability11 UMETA(DisplayName = "Ability11 (P)"),
	Ability12 UMETA(DisplayName = "Ability12 (F)"),
	Ability13 UMETA(DisplayName = "Ability13 (G)"),
	Ability14 UMETA(DisplayName = "Ability14 (H)"),
	Ability15 UMETA(DisplayName = "Ability15 (J)"),
	Ability16 UMETA(DisplayName = "Ability16 (K)"),
	Ability17 UMETA(DisplayName = "Ability17 (L)"),
	Ability19 UMETA(DisplayName = "Ability19 (Space)"),
	Ability20 UMETA(DisplayName = "Ability20 (Shift)"),
	Ability21 UMETA(DisplayName = "Ability21 (1)"),
	Ability22 UMETA(DisplayName = "Ability22 (2)"),
	Ability23 UMETA(DisplayName = "Ability23 (3)"),
	Ability24 UMETA(DisplayName = "Ability24 (4)"),
	Ability25 UMETA(DisplayName = "Ability25 (5)"),
	Ability26 UMETA(DisplayName = "Ability26 (6)"),
	Ability27 UMETA(DisplayName = "Ability27 (7)"),
	Ability29 UMETA(DisplayName = "Ability29 (8)"),
	Ability30 UMETA(DisplayName = "Ability20 (9)"),
	Ability31 UMETA(DisplayName = "Ability31 (0)"),
	Ability32 UMETA(DisplayName = "Ability21 (Z)"),
	Ability33 UMETA(DisplayName = "Ability22 (X)"),
	Ability34 UMETA(DisplayName = "Ability23 (Hold 1)"),
	Ability35 UMETA(DisplayName = "Ability24 (Hold 2)"),
	Ability36 UMETA(DisplayName = "Ability25 (Hold 3)"),
	Ability37 UMETA(DisplayName = "Ability26 (Hold 4)"),
	Ability38 UMETA(DisplayName = "Ability27 (7)"),
	Ability39 UMETA(DisplayName = "Ability29 (8)"),
	Ability40 UMETA(DisplayName = "Ability20 (9)"),
	Ability41 UMETA(DisplayName = "Ability31 (0)"),
	Ability42 UMETA(DisplayName = "Ability31 (C)"),
	Ability43 UMETA(DisplayName = "Ability31 (V)"),
	Ability44 UMETA(DisplayName = "Ability31 (B)"),
	
	// Add your own bindings if you need to.
};

USTRUCT(BlueprintType)
struct GASUTILITY_API FInputGameplayAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category =  "Ability")
	EAbilityInputBindingKey Command = EAbilityInputBindingKey::Ability1;;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category =  "Ability")
	int32 Level = 1;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	TSubclassOf<UGameplayAbility> GameplayAbilityClass;
};

/**
 * Abilities to bind with keys	
 */
USTRUCT(BlueprintType)
struct GASUTILITY_API FDefaultGameplayAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Ability)
	int32 Level = 1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Ability)
	TSubclassOf<UGameplayAbility> GameplayAbilityClass;
};

/**
 * 
 */
UCLASS(Blueprintable)
class GASUTILITY_API UGameplayAbilityCollection : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	// Abilities that are bound to keys
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Collection")
	TArray<FInputGameplayAbilityInfo> BoundAbilities;
	
	// Standard abilities to give to the actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Collection")
	TArray<FDefaultGameplayAbilityInfo> DefaultAbilities;

	void GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAbilitySpecHandle>& BoundHandles, TArray<FGameplayAbilitySpecHandle>& DefaultBoundHandles) const;

	static void RemoveAbilities(UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAbilitySpecHandle> BoundHandles, TArray<FGameplayAbilitySpecHandle> DefaultBoundHandles);
};
