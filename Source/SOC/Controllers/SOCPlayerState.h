// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ObjectiveSystem/Interfaces/ObjectiveAssigneeInterface.h"
#include "SOCPlayerState.generated.h"

class UObjectiveTrackerComponent;
/**
 * 
 */
UCLASS()
class SOC_API ASOCPlayerState : public APlayerState, public IObjectiveAssigneeInterface
{
	GENERATED_BODY()
#pragma region Framework
	ASOCPlayerState();
#pragma endregion

#pragma region Objective System
public:
	virtual UObjectiveAssigneeComponent* GetObjectiveAssigneeComponent() const override {return ObjectiveAssigneeComponent;}

	// Getter function for the ObjectiveAssigneeComponent variable
	UFUNCTION()
	virtual AActor* GetAssignee() override {return this;}
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	UObjectiveAssigneeComponent* ObjectiveAssigneeComponent;
#pragma endregion
};
