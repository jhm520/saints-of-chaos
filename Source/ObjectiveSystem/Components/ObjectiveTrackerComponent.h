// Copyright [2022] Psychedelic Games. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectiveSystem/DataAssets/ObjectiveInfoCollection.h"
#include "ObjectiveTrackerComponent.generated.h"

class UObjectiveInfoCollection;
class AObjective;

//component that tracks objectives
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OBJECTIVESYSTEM_API UObjectiveTrackerComponent : public UActorComponent
{
	GENERATED_BODY()
#pragma region Framework
public:	
	// Sets default values for this component's properties
	UObjectiveTrackerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion

#pragma region Objective System
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	UObjectiveInfoCollection* ObjectiveInfoCollection;

	//sets up the objectives for this tracker
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Objective System")
	void SetupObjectives();
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Objective System")
	void BeginObjectives();
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Objective System")
	void BeginObjective(AObjective* Objective);

	//indicate that an objective has been progressed
	//the assignee is the actor responsible for completing the objective, could be the team associated with the game mode
	//the instigator is the actor that caused the completer to complete the objective, could be a member of the team
	//the objective tag is the tag of the objective that was completed
	//bSuccess indicates whether the objective was completed successfully or if it was failed
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Objective System")
	void ProgressObjective(AActor* Assignee, AActor* Instigator, const FGameplayTag& ObjectiveTag, bool bSuccess = true);

	UFUNCTION()
	void OnObjectiveComplete();
protected:
	AObjective* CreateObjective(const FObjectiveInfo& ObjectiveInfo);

	void SetupObjective(const FObjectiveInfo& ObjectiveInfo);

	void AssignObjective(AObjective* Objective, AActor* Assignee);

	UPROPERTY()
	TArray<AObjective*> Objectives;
#pragma endregion
		
};
