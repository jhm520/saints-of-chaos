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

	virtual USOCAIAvatarComponent* GetAvatarComponent() const override;

	virtual const AActor* GetAvatarActor() const override {return this;};

	virtual void DoAIAction_Implementation(const FSOCAIAction& Action) override;

	virtual void OnEnteredBehavior_Implementation(const FSOCAIAction& InEnteredBehaviorAction, const FSOCAIAction& InExitedBehaviorAction) const override;

	virtual void OnExitedBehavior_Implementation(const FSOCAIAction& InExitedBehaviorAction, const FSOCAIAction& InEnteredBehaviorAction) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	TObjectPtr<USOCAIAvatarComponent> AvatarComponent;

	UFUNCTION()
	void OnDirectorPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn);

#pragma endregion

#pragma region Target Actors
	
	/** Returns the actor that is the target of this ability */
	virtual AActor* GetTargetActor() const override;

#pragma endregion




};
