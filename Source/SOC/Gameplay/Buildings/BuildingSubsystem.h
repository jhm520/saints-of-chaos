// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BuildingSubsystem.generated.h"

class ASOCBuilding;

/**
 * 
 */
UCLASS()
class SOC_API UBuildingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

#pragma region Framework
public:
	UBuildingSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintPure, Category = "Attitude")
	static UBuildingSubsystem* Get(const UObject* WorldContext);
#pragma endregion

#pragma region Building Subsystem
protected:
	UPROPERTY()
	TArray<ASOCBuilding*> RegisteredBuildings;
public:
	
	UFUNCTION(BlueprintCallable, Category = "Attitude")
	void Register(ASOCBuilding* Actor);

	UFUNCTION(BlueprintCallable, Category = "Attitude")
	void Unregister(ASOCBuilding* Actor);
	
	UFUNCTION(BlueprintPure, Category = "Attitude")
	TArray<ASOCBuilding*> GetAllBuildings();
#pragma endregion
	
};
