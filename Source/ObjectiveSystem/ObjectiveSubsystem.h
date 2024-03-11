#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectiveSubsystem.generated.h"

class UObjectiveComponent;
UCLASS()
class OBJECTIVESYSTEM_API UObjectiveSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	
#pragma region Objective System Registry
public:

	UFUNCTION(BlueprintCallable, Category = "Objective System")
	void RegisterObjective(AObjective* Objective);

	UFUNCTION(BlueprintCallable, Category = "Objective System")
	void UnregisterObjective(AObjective* Objective);

	UFUNCTION(BlueprintCallable, Category = "Objective System")
	void RegisterObjectiveComponent(UObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable, Category = "Objective System")
	void UnregisterObjectiveComponent(UObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable, Category = "Objective System")
	void RegisterObjectiveTrackerComponent(UObjectiveTrackerComponent* ObjectiveTrackerComponent);

	UFUNCTION(BlueprintCallable, Category = "Objective System")
	void UnregisterObjectiveTrackerComponent(UObjectiveTrackerComponent* ObjectiveTrackerComponent);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Objective System")
	TArray<TObjectPtr<AObjective>> Objectives;
	
	UPROPERTY(BlueprintReadOnly, Category = "Objective System")
	TArray<TObjectPtr<UObjectiveComponent>> ObjectiveComponents;

	UPROPERTY(BlueprintReadOnly, Category = "Objective System")
	TArray<TObjectPtr<UObjectiveTrackerComponent>> ObjectiveTrackerComponents;

#pragma endregion

	
#pragma region Objective System
protected:

	UObjectiveSubsystem();
public:
	static UObjectiveSubsystem* Get(const UObject* WorldContext);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Objective System")
	void OnObjectiveActorSpawned(AActor* ObjectiveActor, AObjective* Objective);
	
	/** Searches the passed in actor for an ability system component, will use IAbilitySystemInterface or fall back to a component search */
	static UObjectiveComponent* GetObjectiveComponentFromActor(const AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Objective System")
	void ProgressPawnObjective(APawn* Instigator, const FGameplayTag& ObjectiveTag, bool bSuccess = true);

#pragma endregion
	
};
