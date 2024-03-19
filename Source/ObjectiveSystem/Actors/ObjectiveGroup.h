// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "ObjectiveGroup.generated.h"

class AObjectiveGroup;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FOnSubObjectiveSuccessDelegate, AObjectiveGroup*, ObjectiveGroup, AObjective*, Objective, AActor*, Assignee, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FOnSubObjectiveFailureDelegate, AObjectiveGroup*, ObjectiveGroup, AObjective*, Objective, AActor*, Assignee, AActor*, Instigator);

/**
 * 
 */
UCLASS()
class OBJECTIVESYSTEM_API AObjectiveGroup : public AObjective
{
	GENERATED_BODY()
	
protected:

	virtual void OnRegistered() override;

	virtual void OnUnregistered() override;

	UPROPERTY(ReplicatedUsing="OnRep_SubObjectives", Transient, BlueprintReadOnly, Category = "Objective Group")
	TArray<AObjective*> SubObjectives;

	UFUNCTION()
	virtual void OnRep_SubObjectives();
	
	virtual void OnSubObjectivesChanged();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnSubObjectivesChanged"), Category = "Objective Group")
	void K2_OnSubObjectivesChanged();

	UFUNCTION()
	void OnSubObjectiveSuccess(AObjective* Objective, AActor* Assignee, AActor* InInstigator);

	UFUNCTION()
	void OnSubObjectiveFailure(AObjective* Objective, AActor* Assignee, AActor* InInstigator);

	UFUNCTION()
	void OnSubObjectiveComplete(AObjective* Objective, AActor* Assignee, AActor* InInstigator);

	UFUNCTION()
	void OnSubObjectiveFailed(AObjective* Objective, AActor* Assignee, AActor* InInstigator);

	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnSubObjectiveSuccessDelegate OnSubObjectiveSuccessDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnSubObjectiveFailureDelegate OnSubObjectiveFailureDelegate;

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintNativeEvent, Category = "Objective Group")
	bool IsObjectiveGroupComplete() const;

	virtual bool IsObjectiveGroupComplete_Implementation() const;

	
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintNativeEvent, Category = "Objective Group")
	bool IsObjectiveGroupFailed() const;

	virtual bool IsObjectiveGroupFailed_Implementation() const;

	
	TArray<AObjective*> GetSubObjectives() const{return SubObjectives;}

	void AddSubObjective(AObjective* SubObjective);

	void RemoveSubObjective(AObjective* SubObjective);
};
