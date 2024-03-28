// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOCCharacter.h"
#include "CommandSystem/CommandSystemBlueprintLibrary.h"
#include "CommandSystem/Interfaces/CommandableInterface.h"
#include "GAS/Abilities/TargetActors/GameplayAbilityTargetActorInterface.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "CommandSystem/Interfaces/CommandableInterface.h"
#include "SOCAICharacter.generated.h"

class USOCAIBehaviorComponent;
class UCommandableComponent;
//AI Controlled character
UCLASS(Blueprintable)
class SOC_API ASOCAICharacter : public ASOCCharacter, public ISOCAIBehaviorInterface, public IGameplayAbilityTargetActorInterface, public ICommandableInterface
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

	virtual void Reset() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
#pragma endregion

#pragma region Attitude System
public:
	virtual EAttitude GetAttitudeTowards_Implementation(AActor* Other) const override;
#pragma endregion

#pragma region Behavior
protected:
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI Behavior")
	TObjectPtr<USOCAIBehaviorComponent> BehaviorComponent;

public:
	virtual USOCAIBehaviorComponent* GetBehaviorComponent() const override {return BehaviorComponent;};
	
	virtual const AActor* GetAvatarActor() const override {return this;};

	virtual void DoAIAction_Implementation(const FSOCAIAction& Action) override;

	virtual void OnEnteredBehavior_Implementation(const FSOCAIAction& InEnteredBehaviorAction, const FSOCAIAction& InExitedBehaviorAction) const override;

	virtual void OnExitedBehavior_Implementation(const FSOCAIAction& InExitedBehaviorAction, const FSOCAIAction& InEnteredBehaviorAction) const override;
	UFUNCTION()
	void OnDirectorPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn);

#pragma endregion

#pragma region Target Actors
	
	/** Returns the actor that is the target of this ability */
	virtual AActor* GetTargetActor() const override;

#pragma endregion

#pragma region Command

protected:
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI Behavior")
	TObjectPtr<UCommandableComponent> CommandableComponent;
public:
	virtual UCommandableComponent* GetCommandableComponent() const override {return CommandableComponent;};

	virtual void OnCommandBegin_Implementation(const FCommandInstance& Command) override;

	virtual bool CheckCommandFinished_Implementation(const FCommandInstance& Command) const override;
#pragma endregion

#pragma region Damage Causer Interface
	
public:
	virtual AController* GetDamageInstigatorController() const override;
#pragma endregion




};
