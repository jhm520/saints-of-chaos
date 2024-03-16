// Copyright [2022] Psychedelic Games. All rights reserved!


#include "Objective.h"

#include "Net/UnrealNetwork.h"
#include "ObjectiveSystem/ObjectiveSubsystem.h"
#include "ObjectiveSystem/Components/ObjectiveAssigneeComponent.h"
#include "ObjectiveSystem/Interfaces/ObjectiveAssigneeInterface.h"

#pragma region Framework

// Sets default values
AObjective::AObjective()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	CompleteCount = 1;
	FailedCount = 0;
}

// Called when the game starts or when spawned
void AObjective::BeginPlay()
{
	Super::BeginPlay();

	UObjectiveSubsystem* ObjectiveSubsystem = UObjectiveSubsystem::Get(this);

	if (ObjectiveSubsystem)
	{
		ObjectiveSubsystem->RegisterObjective(this);
	}
}

/** Overridable function called whenever this actor is being removed from a level */
void AObjective::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UObjectiveSubsystem* ObjectiveSubsystem = UObjectiveSubsystem::Get(this);

	if (ObjectiveSubsystem)
	{
		ObjectiveSubsystem->UnregisterObjective(this);
	}
	
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AObjective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjective::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(AObjective, ObjectiveStatuses, COND_None, REPNOTIFY_Always);
}
#pragma endregion

#pragma region Objective Status Replication
/*
* Objective Status Events
*/
void AObjective::OnObjectiveStatusAdded(const FObjectiveReplicatorItem& Slot)
{
	
}

void AObjective::OnObjectiveStatusRemoved(const FObjectiveReplicatorItem& Slot)
{
	
}

void AObjective::OnObjectiveStatusChanged(const FObjectiveReplicatorItem& Slot)
{
	
}
#pragma endregion

#pragma region Objective System

void AObjective::Success(AActor* Assignee, AActor* InInstigator)
{
	FObjectiveStatus* FoundAssignee = ObjectiveStatusMap.Find(Assignee);

	if (!FoundAssignee)
	{
		return;
	}
	
	FoundAssignee->SuccessCount++;

	OnObjectiveSuccess.Broadcast(this, Assignee, InInstigator);
	
	if (FoundAssignee->SuccessCount >= CompleteCount)
	{
		Complete(Assignee, InInstigator);
	}

	ReplicateObjectiveStatuses();
}
	
void AObjective::Failure(AActor* Assignee, AActor* InInstigator)
{
	FObjectiveStatus* FoundAssignee = ObjectiveStatusMap.Find(Assignee);

	if (!FoundAssignee)
	{
		return;
	}

	FoundAssignee->FailureCount++;

	OnObjectiveFailure.Broadcast(this, Assignee, InInstigator);
	
	if (FoundAssignee->FailureCount >= FailedCount)
	{
		Failed(Assignee, InInstigator);
	}
	
	ReplicateObjectiveStatuses();
}

void AObjective::Complete(AActor* Assignee, AActor* InInstigator)
{
	bIsComplete = true;
	bIsFailed = false;

	FObjectiveStatus* FoundAssignee = ObjectiveStatusMap.Find(Assignee);

	if (FoundAssignee)
	{
		FoundAssignee->bIsComplete = true;
		FoundAssignee->bIsFailed = false;
	}
	
	OnObjectiveComplete.Broadcast(this, Assignee, InInstigator);
	K2_Complete(Assignee, InInstigator);
}
	
void AObjective::Failed(AActor* Assignee, AActor* InInstigator)
{
	bIsComplete = false;
	bIsFailed = true;

	FObjectiveStatus* FoundAssignee = ObjectiveStatusMap.Find(Assignee);

	if (FoundAssignee)
	{
		FoundAssignee->bIsComplete = false;
		FoundAssignee->bIsFailed = true;
	}
	
	OnObjectiveFailed.Broadcast(this, Assignee, InInstigator);
	K2_Failed(Assignee, InInstigator);
}


void AObjective::ReplicateObjectiveStatuses()
{
	ObjectiveStatusMap.GenerateValueArray(ObjectiveStatuses);

	OnRep_ObjectiveStatuses(ObjectiveStatuses);
}

void AObjective::OnRep_ObjectiveStatuses(const TArray<FObjectiveStatus>& PreviousObjectiveStatuses)
{
	OnObjectiveStatusesChanged(PreviousObjectiveStatuses);
}

void AObjective::OnObjectiveStatusesChanged(const TArray<FObjectiveStatus>& PreviousObjectiveStatuses)
{
	TMap<AActor*, FObjectiveStatus> PreviousObjectiveStatusMap;

	for (const FObjectiveStatus& Status : PreviousObjectiveStatuses)
	{
		PreviousObjectiveStatusMap.Add(Status.Assignee, Status);
	}
	
	for (const FObjectiveStatus& Status : ObjectiveStatuses)
	{
		ObjectiveStatusMap.Add(Status.Assignee, Status);
	}

	TArray<AActor*> Assignees;

	ObjectiveStatusMap.GenerateKeyArray(Assignees);

	for (AActor* Assignee : Assignees)
	{
		FObjectiveStatus* PreviousStatus = PreviousObjectiveStatusMap.Find(Assignee);

		FObjectiveStatus* CurrentStatus = ObjectiveStatusMap.Find(Assignee);

		//if the current status has begun, and the previous status has not, then we have begun the objective
		if (CurrentStatus && CurrentStatus->bHasBegun && (!PreviousStatus || !PreviousStatus->bHasBegun))
		{
			OnBegin(Assignee);
		}
	}
	
	K2_OnObjectiveStatusesChanged();
}

void AObjective::Assign(AActor* Assignee)
{
	if (!HasAuthority())
	{
		return;
	}
	
	if (!Assignee)
	{
		return;
	}
	
	ObjectiveStatusMap.Add(Assignee);

	FObjectiveStatus* FoundAssignee = ObjectiveStatusMap.Find(Assignee);

	if (FoundAssignee)
	{
		FoundAssignee->Assignee = Assignee;
	}

	ReplicateObjectiveStatuses();
}

void AObjective::Unassign(AActor* Assignee)
{
	if (!HasAuthority())
	{
		return;
	}
	
	if (!Assignee)
	{
		return;
	}
	
	ObjectiveStatusMap.Remove(Assignee);

	ReplicateObjectiveStatuses();
}

bool AObjective::IsAssigned(const AActor* Assignee)
{
	return ObjectiveStatusMap.Contains(Assignee);
}

bool AObjective::GetObjectiveStatus(const AActor* Assignee, FObjectiveStatus& OutObjectiveStatus) const
{
	const FObjectiveStatus* StatusPtr = ObjectiveStatusMap.Find(Assignee);

	if (StatusPtr)
	{
		OutObjectiveStatus = *StatusPtr;
		return true;
	}

	return false;
}

TArray<AActor*> AObjective::GetAssignees() const
{
	TArray<AActor*> Assignees;
	ObjectiveStatusMap.GenerateKeyArray(Assignees);

	return Assignees;
}

void AObjective::Begin(const AActor* Assignee)
{
	if (!HasAuthority())
	{
		return;
	}
	
	FObjectiveStatus* FoundAssignee = ObjectiveStatusMap.Find(Assignee);
	
	if (FoundAssignee)
	{
		FoundAssignee->bHasBegun = true;
	}
	
	ReplicateObjectiveStatuses();
}

void AObjective::OnBegin(AActor* Assignee)
{
	K2_Begin(Assignee);
}

//begin this objective, and indicate to the assignee that they should start working on completing the objective
//begin this objective, and indicate to all assignees that they should start working on completing the objective
void AObjective::BeginAllAssignees()
{
	if (!HasAuthority())
	{
		return;
	}
	
	TArray<AActor*> Assignees = GetAssignees();

	for (AActor* Assignee : Assignees)
	{
		Begin(Assignee);
	}

	ReplicateObjectiveStatuses();
}

bool AObjective::HasBegun(const AActor* Assignee) const
{
	if (const FObjectiveStatus* FoundAssignee = ObjectiveStatusMap.Find(Assignee))
	{
		return FoundAssignee->bHasBegun;
	}

	return false;
}


#pragma endregion
