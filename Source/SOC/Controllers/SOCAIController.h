// Fill out your copyright notice in the Description page of Project Settings.
#pragma region Include

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AggroSystem/Interfaces/AggroInterface.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "SOCAIController.generated.h"
#pragma endregion

/**
 * 
 */

class USOCAIBehaviorComponent;
class UAggroSystemComponent;

UCLASS(Blueprintable)
class SOC_API ASOCAIController : public AAIController, public ISOCAIBehaviorInterface, public IAggroInterface
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

#pragma region Behavior Inteface

	virtual void DoAIAction_Implementation(const FSOCAIAction& Action) override;

	virtual AActor* GetAvatarActor() const override {return GetPawn();};

	virtual USOCAIBehaviorComponent* GetBehaviorComponent() const override {return BehaviorComponent;};
#pragma endregion

#pragma region Aggro System
public:
	virtual UAggroSystemComponent* GetAggroSystemComponent() const override;

#pragma endregion 

};
