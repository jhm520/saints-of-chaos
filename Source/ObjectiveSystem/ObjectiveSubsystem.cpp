#include "ObjectiveSubsystem.h"
#include "Components/ObjectiveComponent.h"
#include "Interfaces/ObjectiveInterface.h"

UObjectiveSubsystem::UObjectiveSubsystem()
{
	
}
	
UObjectiveSubsystem* UObjectiveSubsystem::Get(const UObject* WorldContext)
{
	if(!WorldContext)
	{
		return nullptr;
	}
	
	if(const UWorld* World = WorldContext->GetWorld())
	{
		return World->GetSubsystem<UObjectiveSubsystem>();
	}
	
	return nullptr;
}

void UObjectiveSubsystem::RegisterObjective(AObjective* Objective)
{
	Objectives.Add(Objective);
}

void UObjectiveSubsystem::UnregisterObjective(AObjective* Objective)
{
	Objectives.Remove(Objective);
}

void UObjectiveSubsystem::RegisterObjectiveComponent(UObjectiveComponent* ObjectiveComponent)
{
	ObjectiveComponents.Add(ObjectiveComponent);
}

void UObjectiveSubsystem::UnregisterObjectiveComponent(UObjectiveComponent* ObjectiveComponent)
{
	ObjectiveComponents.Remove(ObjectiveComponent);
}

void UObjectiveSubsystem::OnObjectiveActorSpawned(AActor* ObjectiveActor, AObjective* Objective)
{
	if (!ObjectiveActor)
	{
		return;
	}

	if (!ObjectiveActor)
	{
		return;
	}

	IObjectiveInterface* ObjectiveInterface = Cast<IObjectiveInterface>(ObjectiveActor);

	if (!ObjectiveInterface)
	{
		return;
	}

	UObjectiveComponent* ObjectiveComponent = ObjectiveInterface->GetObjectiveComponent();

	if (!ObjectiveComponent)
	{
		return;
	}

	ObjectiveComponent->SetObjective(Objective);
}


UObjectiveComponent* UObjectiveSubsystem::GetObjectiveComponentFromActor(const AActor* Actor)
{
	if (Actor == nullptr)
	{
		return nullptr;
	}

	const IObjectiveInterface* ObjectiveInterface = Cast<IObjectiveInterface>(Actor);
	
	if (ObjectiveInterface)
	{
		return ObjectiveInterface->GetObjectiveComponent();
	}

	return nullptr;
}

void UObjectiveSubsystem::ProgressPawnObjective(APawn* Instigator, const FGameplayTag& ObjectiveTag, bool bSuccess)
{
	
}
