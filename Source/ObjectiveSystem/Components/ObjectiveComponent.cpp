//


#include "ObjectiveComponent.h"

#include "ObjectiveSystem/ObjectiveSubsystem.h"

// Sets default values for this component's properties
UObjectiveComponent::UObjectiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectiveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UObjectiveSubsystem* ObjectiveSubsystem = UObjectiveSubsystem::Get(this);

	if (ObjectiveSubsystem)
	{
		ObjectiveSubsystem->RegisterObjectiveComponent(this);
	}
}

void UObjectiveComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// ...
	UObjectiveSubsystem* ObjectiveSubsystem = UObjectiveSubsystem::Get(this);

	if (ObjectiveSubsystem)
	{
		ObjectiveSubsystem->UnregisterObjectiveComponent(this);
	}
	
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void UObjectiveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

