#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MinimapSubsystem.generated.h"

UCLASS()
class MINIMAPSYSTEM_API UMinimapSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	
#pragma region Objective System Registry
public:

	UFUNCTION(BlueprintCallable, Category = "Objective System")
	void RegisterMinimapItem(UMinimapItemComponent* MinimapItemComponent);

	UFUNCTION(BlueprintCallable, Category = "Objective System")
	void UnregisterMinimapItem(UMinimapItemComponent* MinimapItemComponent);

	UPROPERTY(BlueprintReadOnly, Category = "Objective System")
	TArray<UMinimapItemComponent*> MinimapItems;
#pragma endregion

	
#pragma region Objective System
protected:

	UMinimapSubsystem();
public:
	static UMinimapSubsystem* Get(const UObject* WorldContext);
#pragma endregion
	
};
