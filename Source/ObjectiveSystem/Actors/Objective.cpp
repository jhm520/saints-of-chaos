// Copyright [2022] Psychedelic Games. All rights reserved!


#include "Objective.h"

#include "ObjectiveSystem/ObjectiveSubsystem.h"
#include "ObjectiveSystem/Components/ObjectiveAssigneeComponent.h"
#include "ObjectiveSystem/Interfaces/ObjectiveAssigneeInterface.h"

#pragma region Framework

// Sets default values
AObjective::AObjective()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SuccessCount = 1;
	FailureCount = 0;

	bHasBegun = false;

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
	
	if (FoundAssignee->SuccessCount >= SuccessCount)
	{
		Complete(Assignee, InInstigator);
	}
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
	
	if (FoundAssignee->FailureCount >= FailureCount)
	{
		Failed(Assignee, InInstigator);
	}
}

void AObjective::Complete(AActor* Assignee, AActor* InInstigator)
{
	bIsComplete = true;
	bIsFailed = false;
	OnObjectiveComplete.Broadcast(this, Assignee, InInstigator);
	K2_Complete(Assignee, InInstigator);
}
	
void AObjective::Failed(AActor* Assignee, AActor* InInstigator)
{
	bIsComplete = false;
	bIsFailed = true;
	OnObjectiveFailed.Broadcast(this, Assignee, InInstigator);
	K2_Failed(Assignee, InInstigator);
}

void AObjective::Assign(AActor* Assignee)
{
	if (!Assignee)
	{
		return;
	}
	
	ObjectiveStatusMap.Add(Assignee);
}

void AObjective::Unassign(AActor* Assignee)
{
	if (!Assignee)
	{
		return;
	}
	
	ObjectiveStatusMap.Remove(Assignee);
}

bool AObjective::IsAssigned(const AActor* Assignee)
{
	return ObjectiveStatusMap.Find(Assignee) != nullptr;
}

void AObjective::Begin()
{
	if (bHasBegun)
	{
		return;
	}
	
	bHasBegun = true;
	
	K2_Begin();
}

bool AObjective::HasBegun() const
{
	return bHasBegun;
}


#pragma endregion
