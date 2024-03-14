// Copyright [2022] Psychedelic Games. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
#include "ObjectiveSystem/DataAssets/ObjectiveInfoCollection.h"
#include "Objective.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnObjectiveSuccessDelegate, AObjective*, Objective);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnObjectiveFailedDelegate, AObjective*, Objective);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnObjectiveCompleteDelegate, AObjective*, Objective);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnObjectiveFailureDelegate, AObjective*, Objective);



UCLASS()
class OBJECTIVESYSTEM_API AObjective : public AActor
{
	GENERATED_BODY()
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

#pragma region Objective System

	//a descriptor and ID tag for this objective
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	FGameplayTagContainer ObjectiveTags;

	//The number of times this objective must be completed to be considered successfully completed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	int32 SuccessCount;
	
	//The number of times this objective must be failed for this objective to be considered failed
	//A value of zero means that this objective cannot be failed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	int32 FailureCount;

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

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Objective Success"), Category = "Objective System")
	void K2_Complete(AActor* Assignee, AActor* InInstigator);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Objective Failure"), Category = "Objective System")
	void K2_Failed(AActor* Assignee, AActor* InInstigator);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Begin Objective"), Category = "Objective System")
	void K2_Begin();

	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnObjectiveSuccessDelegate OnObjectiveSuccess;
	
	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnObjectiveFailureDelegate OnObjectiveFailure;

	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnObjectiveCompleteDelegate OnObjectiveComplete;

	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnObjectiveFailedDelegate OnObjectiveFailed;

	UPROPERTY()
	TMap<AActor*, FObjectiveStatus> ObjectiveStatusMap;

public:
	//assign an actor to this objective
	void Assign(AActor* Assignee);

	//unassign an actor from this objective
	void Unassign(AActor* Assignee);

	bool IsAssigned(const AActor* Assignee);

	//begin this objective, and indicate to the assignees that they should start working on completing the objective
	void Begin();

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Objective System")
	bool bHasBegun;

#pragma endregion

};
