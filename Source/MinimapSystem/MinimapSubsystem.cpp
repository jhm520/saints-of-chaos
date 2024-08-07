#include "MinimapSubsystem.h"

UMinimapSubsystem::UMinimapSubsystem()
{
	
}
	
UMinimapSubsystem* UMinimapSubsystem::Get(const UObject* WorldContext)
{
	if(!WorldContext)
	{
		return nullptr;
	}
	
	if(const UWorld* World = WorldContext->GetWorld())
	{
		return World->GetSubsystem<UMinimapSubsystem>();
	}
	
	return nullptr;
}

void UMinimapSubsystem::RegisterMinimapItem(UMinimapItemComponent* MinimapItemComponent)
{
	MinimapItems.Add(MinimapItemComponent);
}

void UMinimapSubsystem::UnregisterMinimapItem(UMinimapItemComponent* MinimapItemComponent)
{
	MinimapItems.Remove(MinimapItemComponent);
}