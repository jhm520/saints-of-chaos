#include "AttitudeSubsystem.h"

UAttitudeSubsystem::UAttitudeSubsystem()
{
}

void UAttitudeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UAttitudeSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

UAttitudeSubsystem* UAttitudeSubsystem::Get(const UObject* WorldContext)
{
	if(!WorldContext)
	{
		return nullptr;
	}
	
	if(const UWorld* World = WorldContext->GetWorld())
	{
		return World->GetSubsystem<UAttitudeSubsystem>();
	}
	
	return nullptr;
}

void UAttitudeSubsystem::Register(AActor* Actor)
{
	RegisteredActors.Add(Actor);
}

void UAttitudeSubsystem::Unregister(AActor* Actor)
{
	RegisteredActors.Remove(Actor);
}

void UAttitudeSubsystem::AttitudeChanged(AActor* Actor)
{
	OnAttitudeChanged.Broadcast(Actor);
}

TArray<AActor*> UAttitudeSubsystem::GetAllActorsWithAttitudeTowards(AActor* Towards, EAttitude Attitude, bool bIncludeChildActors)
{
	TArray<AActor*> OutActors;

	for (AActor* RegisteredActor : RegisteredActors)
	{
		if (RegisteredActor->Implements<UAttitudeInterface>())
		{
			if(Attitude == IAttitudeInterface::Execute_GetAttitudeTowards(RegisteredActor, Towards))
			{
				OutActors.Add(RegisteredActor);
				if(bIncludeChildActors)
				{
					RegisteredActor->GetAllChildActors(OutActors, true);
				}
			}
		}
	}
		
	return OutActors;
}

TArray<AActor*> UAttitudeSubsystem::GetAllActorsWithAttitudesTowards(AActor* Towards, TSet<EAttitude> Attitudes, bool bIncludeChildActors)
{
	TArray<AActor*> OutActors;

	for (AActor* RegisteredActor : RegisteredActors)
	{
		if (RegisteredActor->Implements<UAttitudeInterface>())
		{
			if(Attitudes.Contains(IAttitudeInterface::Execute_GetAttitudeTowards(RegisteredActor, Towards)))
			{
				OutActors.Add(RegisteredActor);
				if(bIncludeChildActors)
				{
					RegisteredActor->GetAllChildActors(OutActors, true);

					// Also get attached actors:
					RegisteredActor->GetAttachedActors(OutActors, false, true);
				}
			}
		}
	}
	
	return OutActors;
}

TArray<AActor*> UAttitudeSubsystem::GetAllActorsWithAttitude()
{
	return RegisteredActors;
}