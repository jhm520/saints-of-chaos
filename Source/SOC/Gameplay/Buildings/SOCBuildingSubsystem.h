// © 2024 Jade Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SOCBuildingSubsystem.generated.h"

class ASOCBuilding;

/**
 * 
 */
UCLASS()
class SOC_API USOCBuildingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

#pragma region Framework
public:
	USOCBuildingSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintPure, Category = "Attitude")
	static USOCBuildingSubsystem* Get(const UObject* WorldContext);
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
