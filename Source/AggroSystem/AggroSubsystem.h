#pragma once

#include "CoreMinimal.h"

#include "AggroSubsystem.generated.h"


/**
 * 
 */
UCLASS()
class AGGROSYSTEM_API UAggroSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	
#pragma region Framework
public:
	UAggroSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintPure, Category = "Attitude")
	static UAggroSubsystem* Get(const UObject* WorldContext);
#pragma endregion
	
};
