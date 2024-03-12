// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "CoreUtility/Attitude/AttitudeInterface.h"
#include "CoreUtility/AutoOwnership/Components/AutoOwnershipComponent.h"
#include "CoreUtility/Clicking/Interfaces/ClickingInterface.h"
#include "GameFramework/PlayerController.h"
#include "SelectionSystem/Interfaces/SelectorInterface.h"
#include "SOCPlayerController.generated.h"

class UAutoOwnershipComponent;

/**
 * 
 */

UCLASS()
class SOC_API ASOCPlayerController : public APlayerController, public IAttitudeInterface, public ISelectorInterface, public IAbilitySystemInterface, public IClickingInterface
{
	GENERATED_BODY()
#pragma region Framework
public:
	// Sets default values for this character's properties
	ASOCPlayerController();
#pragma endregion

#pragma region Auto Ownership
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAutoOwnershipComponent> AutoOwnershipComponent;

#pragma endregion

#pragma region Debug

	// Sets default values for this character's properties
	UFUNCTION(Exec, BlueprintCallable, Category = "Debug Commands")
	void DebugSpawnMobs();

	UFUNCTION(Server, Reliable)
	void Server_DebugSpawnMobs();

	// Starts the game match
	UFUNCTION(Exec, BlueprintCallable, Category = "Debug Commands")
	void DebugStartMatch();

	UFUNCTION(Server, Reliable)
	void Server_DebugStartMatch();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug Commands")
	TSubclassOf<class UGameplayAbility> MobSpawnAbilityClass;
#pragma endregion

#pragma region Gameplay Abilities
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

#pragma endregion

#pragma region Attitude

	EAttitude GetAttitudeTowards_Implementation(AActor* Other) const;

#pragma endregion

#pragma region Selection System

public:
	virtual USelectorComponent* GetSelectorComponent() const override;

#pragma endregion

#pragma region Clicking
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Clicking")
	TObjectPtr<UClickingComponent> ClickingComponent;
	
public:

	virtual UClickingComponent* GetClickingComponent() const;

#pragma endregion

};
