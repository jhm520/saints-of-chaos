// Fill out your copyright notice in the Description page of Project Settings.
#pragma region Include

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AIController.h"
#include "AggroSystem/Interfaces/AggroInterface.h"
#include "CoreUtility/Attitude/AttitudeInterface.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "SOCAIController.generated.h"
#pragma endregion

/**
 * 
 */

class USOCAIBehaviorComponent;
class UAggroSystemComponent;

UCLASS(Blueprintable)
class SOC_API ASOCAIController : public AAIController, public ISOCAIBehaviorInterface, public IAttitudeInterface, public IAggroInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
#pragma region Framework

public:
	ASOCAIController(const FObjectInitializer& ObjectInitializer);

	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(const float DeltaSeconds) override;
	
#pragma endregion 

#pragma region Behavior Component
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI Behavior")
	TObjectPtr<USOCAIBehaviorComponent> BehaviorComponent;

#pragma endregion

#pragma region Actions

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI Actions")
	float MovementAcceptanceRadius;

#pragma endregion

#pragma region Behavior Inteface

	virtual void DoAIAction_Implementation(const FSOCAIAction& Action) override;

	virtual void DoAIAction_MoveToLocation(const FSOCAIAction& Action) const;

	virtual const AActor* GetAvatarActor() const override {return GetPawn();};

	virtual USOCAIBehaviorComponent* GetBehaviorComponent() const override;
	
	virtual void OnEnteredBehavior_Implementation(const FSOCAIAction& InEnteredBehaviorAction, const FSOCAIAction& InExitedBehaviorAction) const override;

	virtual void OnExitedBehavior_Implementation(const FSOCAIAction& InExitedBehaviorAction, const FSOCAIAction& InEnteredBehaviorAction) const override;

#pragma endregion

#pragma region Aggro System
public:
	virtual UAggroSystemComponent* GetAggroSystemComponent() const override;

	virtual bool ShouldAggro(AActor* AggroTarget) const override;

#pragma endregion

#pragma region Attitude System
public:
	virtual EAttitude GetAttitudeTowards_Implementation(AActor* Other) const override;
#pragma endregion

#pragma region Ability System

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
#pragma endregion

};
