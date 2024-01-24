// Fill out your copyright notice in the Description page of Project Settings.
#pragma region Include

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SOCAIController.generated.h"
#pragma endregion

/**
 * 
 */

class USOCAIBehaviorComponent;

UCLASS(Blueprintable)
class SOCAI_API ASOCAIController : public AAIController
{
	GENERATED_BODY()
	
#pragma region Framework

public:
	ASOCAIController(const FObjectInitializer& ObjectInitializer);

	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(const float DeltaSeconds) override;
	
#pragma endregion 

#pragma region Behavior component
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI Behavior")
	TObjectPtr<USOCAIBehaviorComponent> BehaviorComponent;

#pragma endregion 
	
};
