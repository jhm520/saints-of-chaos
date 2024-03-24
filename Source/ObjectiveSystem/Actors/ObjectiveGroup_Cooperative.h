// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectiveGroup.h"
#include "ObjectiveGroup_Cooperative.generated.h"

/**
 * 
 */
UCLASS()
class OBJECTIVESYSTEM_API AObjectiveGroup_Cooperative : public AObjectiveGroup
{
	GENERATED_BODY()

#pragma region ObjectiveGroup

	virtual void SetupSubObjectives_Implementation() override;

	virtual void GetObjectiveGroupAssignees_Implementation(TArray<AActor*>& OutAssignees) override;

#pragma endregion

};
