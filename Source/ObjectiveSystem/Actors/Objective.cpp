// Copyright [2022] Psychedelic Games. All rights reserved!


#include "Objective.h"

#include "ObjectiveSystem/ObjectiveSubsystem.h"

#pragma region Framework

// Sets default values
AObjective::AObjective()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SuccessCount = 1;
	FailureCount = 0;

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
	
	if (FoundAssignee->FailureCount >= FailureCount)
	{
		Failed(Assignee, InInstigator);
	}
}

void AObjective::Complete(AActor* Assignee, AActor* InInstigator)
{
	K2_Complete(Assignee, InInstigator);
}
	
void AObjective::Failed(AActor* Assignee, AActor* InInstigator)
{
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

void AObjective::Begin()
{
	K2_Begin();
}

#pragma endregion