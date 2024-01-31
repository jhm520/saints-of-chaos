// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "CoreUtility/AutoOwnership/Interfaces/AutoOwnershipInterface.h"
#include "GameFramework/Pawn.h"
#include "GameplayTagContainer.h"
#include "CoreUtility/Attitude/AttitudeInterface.h"
#include "Building.generated.h"

class UGameplayAbilityCollection;
class UAbilitySystemComponent;

UCLASS()
class SOC_API ASOCBuilding : public APawn, public IAbilitySystemInterface, public IAutoOwnershipInterface, public IAttitudeInterface
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
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
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

};
