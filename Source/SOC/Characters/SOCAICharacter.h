// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOCCharacter.h"
#include "GAS/Abilities/TargetActors/GameplayAbilityTargetActorInterface.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "SOCAICharacter.generated.h"

class USOCAIBehaviorComponent;
//AI Controlled character
UCLASS(Blueprintable)
class SOC_API ASOCAICharacter : public ASOCCharacter, public ISOCAIBehaviorInterface, public IGameplayAbilityTargetActorInterface
{
	GENERATED_BODY()

#pragma region Framework
public:
	// Sets default values for this character's properties
	ASOCAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetOwner( AActor* NewOwner ) override;

	virtual void SpawnDefaultController() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion

#pragma region Attitude System
public:
	virtual EAttitude GetAttitudeTowards_Implementation(AActor* Other) const override;
#pragma endregion

#pragma region Behavior

	virtual USOCAIBehaviorComponent* GetBehaviorComponent() const override;

	virtual const AActor* GetAvatarActor() const override {return this;};

	virtual void OnEnteredBehavior_Implementation(const FSOCAIAction& InEnteredBehaviorAction, const FSOCAIAction& InExitedBehaviorAction) const override;

	virtual void OnExitedBehavior_Implementation(const FSOCAIAction& InExitedBehaviorAction, const FSOCAIAction& InEnteredBehaviorAction) const override;

#pragma endregion

#pragma region Target Actors
	
	/** Returns the actor that is the target of this ability */
	virtual AActor* GetTargetActor() const override;

#pragma endregion




};
