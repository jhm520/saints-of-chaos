// © 2024 John Henry Miller. All rights reserved

#include "BuildingSubsystem.h"

#pragma region Framework
UBuildingSubsystem::UBuildingSubsystem()
{
	
}
	
void UBuildingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UBuildingSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

UBuildingSubsystem* UBuildingSubsystem::Get(const UObject* WorldContext)
{
	if(!WorldContext)
	{
		return nullptr;
	}
	
	if(const UWorld* World = WorldContext->GetWorld())
	{
		return World->GetSubsystem<UBuildingSubsystem>();
	}
	
	return nullptr;
}
#pragma endregion

#pragma region Building Subsystem

void UBuildingSubsystem::Register(ASOCBuilding* Actor)
{
	RegisteredBuildings.Add(Actor);
}

void UBuildingSubsystem::Unregister(ASOCBuilding* Actor)
{
	RegisteredBuildings.Remove(Actor);
}

TArray<ASOCBuilding*> UBuildingSubsystem::GetAllBuildings()
{
	return RegisteredBuildings;
}

#pragma endregion