// Copyright [2022] Psychedelic Games. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
#include "ObjectiveSystem/DataAssets/ObjectiveInfoCollection.h"
#include "Objective.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnObjectiveSuccessDelegate, AObjective*, Objective, AActor*, Assignee, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnObjectiveFailedDelegate, AObjective*, Objective, AActor*, Assignee, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnObjectiveCompleteDelegate, AObjective*, Objective, AActor*, Assignee, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnObjectiveFailureDelegate, AObjective*, Objective, AActor*, Assignee, AActor*, Instigator);



UCLASS(Blueprintable)
class OBJECTIVESYSTEM_API AObjective : public AInfo
{
	GENERATED_BODY()

	friend class UObjectiveSubsystem;
	friend class UObjectiveTrackerComponent;
	friend struct FObjectiveReplicator;
	friend struct FObjectiveReplicatorItem;
#pragma region Objective System

public:	
	// Sets default values for this actor's properties
	AObjective();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/** Overridable function called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
#pragma endregion

#pragma region Objective Status Replication
	/*
* Objective Status Events
*/
	virtual void OnObjectiveStatusAdded(const FObjectiveReplicatorItem& Slot);
	virtual void OnObjectiveStatusRemoved(const FObjectiveReplicatorItem& Slot);
	virtual void OnObjectiveStatusChanged(const FObjectiveReplicatorItem& Slot);
#pragma endregion

#pragma region Objective System
protected:

	virtual void OnRegistered();

	virtual void OnUnregistered();

	//a descriptor and ID tag for this objective
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	FGameplayTagContainer ObjectiveTags;

	//The number of times this objective must be completed to be considered successfully completed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	int32 CompleteCount;
	
	//The number of times this objective must be failed for this objective to be considered failed
	//A value of zero means that this objective cannot be failed, but the failure count will still increment
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	int32 FailedCount;

	//increment the success count of this objective,
	//the assignee is the actor that caused this objective to succeed (the team)
	//the instigator is the actor that caused the succeeder to succeed (member of the team)
	void Success(AActor* Assignee, AActor* Instigator);

	//increment the failure count of this objective,
	//the assignee is the actor that caused this objective to fail (the team)
	//the instigator is the actor that caused the failer to fail (member of the team)
	void Failure(AActor* Assignee, AActor* Instigator);

	virtual void Complete(AActor* Assignee, AActor* InInstigator);

	virtual void Failed(AActor* Assignee, AActor* InInstigator);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Objective Complete"), Category = "Objective System")
	void K2_Complete(AActor* Assignee, AActor* InInstigator);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Objective Failed"), Category = "Objective System")
	void K2_Failed(AActor* Assignee, AActor* InInstigator);

	virtual void OnSetup();
	
	virtual void OnBegin(AActor* Assignee);
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Begin Objective"), Category = "Objective System")
	void K2_Begin(const AActor* Assignee);

	UPROPERTY()
	TMap<AActor*, FObjectiveStatus> ObjectiveStatusMap;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_ObjectiveStatuses", Category = "Objective System")
	TArray<FObjectiveStatus> ObjectiveStatuses;

	UFUNCTION()
	void ReplicateObjectiveStatuses();
	
	UFUNCTION()
	void OnRep_ObjectiveStatuses(const TArray<FObjectiveStatus>& PreviousObjectiveStatuses);

	void OnObjectiveStatusesChanged(const TArray<FObjectiveStatus>& PreviousObjectiveStatuses);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Objective Statuses Changed"), Category = "Objective System")
	void K2_OnObjectiveStatusesChanged();

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Objective System")
	bool bIsComplete;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Objective System")
	bool bIsFailed;
public:
	//assign an actor to this objective
	void Assign(AActor* Assignee);

	//unassign an actor from this objective
	void Unassign(AActor* Assignee);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Objective System")
	bool IsAssigned(const AActor* Assignee);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Objective System")
	bool GetObjectiveStatus(const AActor* Assignee, FObjectiveStatus& OutObjectiveStatus) const;

	//returns true if the specified assignee has completed this objective
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Objective System")
	bool HasAssigneeCompleted(const AActor* Assignee) const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Objective System")
	TArray<AActor*> GetAssignees() const;

	//begin this objective, and indicate to the assignee that they should start working on completing the objective
	virtual void Begin(const AActor* Assignee);
	
	//begin this objective, and indicate to all assignees that they should start working on completing the objective
	void BeginAllAssignees();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Objective System")
	bool HasBegun(const AActor* Assignee) const;

	//returns true if any assignee has completed this objective
	bool IsComplete() const {return bIsComplete;}

	//returns true if any assignee has failed this objective
	bool IsFailed() const {return bIsFailed;}

	int32 GetSuccessCount() const {return CompleteCount;}

	int32 GetFailureCount() const {return FailedCount;}

	const FGameplayTagContainer& GetObjectiveTags() const {return ObjectiveTags;}
	

	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnObjectiveSuccessDelegate OnObjectiveSuccess;
	
	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnObjectiveFailureDelegate OnObjectiveFailure;

	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnObjectiveCompleteDelegate OnObjectiveComplete;

	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnObjectiveFailedDelegate OnObjectiveFailed;

#pragma endregion

};
