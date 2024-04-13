// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "ObjectiveGroup.generated.h"

class AObjectiveGroup;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FOnSubObjectiveSuccessDelegate, AObjectiveGroup*, ObjectiveGroup, AObjective*, Objective, AActor*, Assignee, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FOnSubObjectiveFailureDelegate, AObjectiveGroup*, ObjectiveGroup, AObjective*, Objective, AActor*, Assignee, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FOnSubObjectiveCompleteDelegate, AObjectiveGroup*, ObjectiveGroup, AObjective*, Objective, AActor*, Assignee, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams( FOnSubObjectiveFailedDelegate, AObjectiveGroup*, ObjectiveGroup, AObjective*, Objective, AActor*, Assignee, AActor*, Instigator);

/**
 * 
 */
UCLASS()
class OBJECTIVESYSTEM_API AObjectiveGroup : public AObjective
{
	GENERATED_BODY()

#pragma region Framework

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
#pragma endregion

#pragma region Objective
protected:

	virtual void OnRegistered() override;

	virtual void OnUnregistered() override;

	virtual void OnSetup() override;
	
	virtual void OnBegin(AActor* Assignee) override;

	virtual void Begin(const AActor* Assignee);


#pragma endregion

#pragma region Objective Group
protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Objective Group")
	void SetupSubObjectives();

	virtual void SetupSubObjectives_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Objective Group")
	void GetObjectiveGroupAssignees(TArray<AActor*>& OutAssignees);

	virtual void GetObjectiveGroupAssignees_Implementation(TArray<AActor*>& OutAssignees);
private:
	UPROPERTY(ReplicatedUsing="OnRep_SubObjectives", Transient)
	TArray<AObjective*> SubObjectives;
protected:
	//the tags of the sub objectives used for setup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	FGameplayTagContainer SubObjectiveTags;

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

public:
	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnSubObjectiveSuccessDelegate OnSubObjectiveSuccessDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnSubObjectiveFailureDelegate OnSubObjectiveFailureDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnSubObjectiveCompleteDelegate OnSubObjectiveCompleteDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnSubObjectiveFailedDelegate OnSubObjectiveFailedDelegate;

	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintNativeEvent, Category = "Objective Group")
	bool IsObjectiveGroupComplete() const;

	virtual bool IsObjectiveGroupComplete_Implementation() const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintNativeEvent, Category = "Objective Group")
	bool IsObjectiveGroupFailed() const;

	virtual bool IsObjectiveGroupFailed_Implementation() const;

	UFUNCTION(BlueprintPure, Category = "Objective Group")
	TArray<AObjective*> GetSubObjectives() const{return SubObjectives;}

	void AddSubObjective(AObjective* SubObjective);

	void RemoveSubObjective(AObjective* SubObjective);

#pragma endregion
};
