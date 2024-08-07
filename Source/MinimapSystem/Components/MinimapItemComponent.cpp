// © 2024 John Henry Miller. All rights reserved


#include "MinimapItemComponent.h"

#include "MinimapSystem/MinimapSubsystem.h"

// Sets default values for this component's properties
UMinimapItemComponent::UMinimapItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMinimapItemComponent::BeginPlay()
{
	Super::BeginPlay();

	UMinimapSubsystem* MinimapSubsystem = UMinimapSubsystem::Get(GetWorld());

	if (MinimapSubsystem)
	{
		MinimapSubsystem->RegisterMinimapItem(this);
	}
	// ...
	
}

void UMinimapItemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UMinimapSubsystem* MinimapSubsystem = UMinimapSubsystem::Get(GetWorld());

	if (MinimapSubsystem)
	{
		MinimapSubsystem->UnregisterMinimapItem(this);
	}

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void UMinimapItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

