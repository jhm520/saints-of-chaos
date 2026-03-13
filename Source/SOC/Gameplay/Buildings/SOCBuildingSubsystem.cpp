// © 2024 Jade Miller. All rights reserved

#include "SOCBuildingSubsystem.h"

#pragma region Framework
USOCBuildingSubsystem::USOCBuildingSubsystem()
{
	
}
	
void USOCBuildingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USOCBuildingSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

USOCBuildingSubsystem* USOCBuildingSubsystem::Get(const UObject* WorldContext)
{
	if(!WorldContext)
	{
		return nullptr;
	}
	
	if(const UWorld* World = WorldContext->GetWorld())
	{
		return World->GetSubsystem<USOCBuildingSubsystem>();
	}
	
	return nullptr;
}
#pragma endregion

#pragma region Building Subsystem

void USOCBuildingSubsystem::Register(ASOCBuilding* Actor)
{
	RegisteredBuildings.Add(Actor);
}

void USOCBuildingSubsystem::Unregister(ASOCBuilding* Actor)
{
	RegisteredBuildings.Remove(Actor);
}

TArray<ASOCBuilding*> USOCBuildingSubsystem::GetAllBuildings()
{
	return RegisteredBuildings;
}

#pragma endregion