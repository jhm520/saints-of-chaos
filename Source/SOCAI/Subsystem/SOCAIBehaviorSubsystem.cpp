// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehaviorSubsystem.h"
#include "SOCAI/Behavior/SOCAIBehaviorManager.h"

#pragma region Framework
USOCAIBehaviorSubsystem::USOCAIBehaviorSubsystem()
{
	
}
	
void USOCAIBehaviorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USOCAIBehaviorSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

USOCAIBehaviorSubsystem* USOCAIBehaviorSubsystem::Get(const UObject* WorldContext)
{
	if(!WorldContext)
	{
		return nullptr;
	}
	
	if(const UWorld* World = WorldContext->GetWorld())
	{
		return World->GetSubsystem<USOCAIBehaviorSubsystem>();
	}
	
	return nullptr;
}
#pragma endregion

#pragma region Behavior Subsystem

void USOCAIBehaviorSubsystem::Register(ASOCAIBehaviorManager* Actor)
{
	RegisteredBehaviorManagers.AddUnique(Actor);
}

void USOCAIBehaviorSubsystem::Unregister(ASOCAIBehaviorManager* Actor)
{
	RegisteredBehaviorManagers.Remove(Actor);
}

TArray<ASOCAIBehaviorManager*> USOCAIBehaviorSubsystem::GetAllBehaviorManagers()
{
	return RegisteredBehaviorManagers;
}

USOCAIBehavior* USOCAIBehaviorSubsystem::GetBehavior(const FGameplayTag& InBehaviorTag)
{
	TArray<ASOCAIBehaviorManager*> BehaviorManagers = GetAllBehaviorManagers();

	for (ASOCAIBehaviorManager* Manager : BehaviorManagers)
	{
		if (!Manager)
		{
			continue;
		}

		USOCAIBehavior* Behavior = Manager->GetBehavior(InBehaviorTag);

		if (Behavior)
		{
			return Behavior;
		}
	}

	return nullptr;
}

#pragma endregion