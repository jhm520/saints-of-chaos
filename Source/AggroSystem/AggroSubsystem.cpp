#include "AggroSubsystem.h"

UAggroSubsystem::UAggroSubsystem()
{
}

void UAggroSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UAggroSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

UAggroSubsystem* UAggroSubsystem::Get(const UObject* WorldContext)
{
	if(!WorldContext)
	{
		return nullptr;
	}
	
	if(const UWorld* World = WorldContext->GetWorld())
	{
		return World->GetSubsystem<UAggroSubsystem>();
	}
	
	return nullptr;
}