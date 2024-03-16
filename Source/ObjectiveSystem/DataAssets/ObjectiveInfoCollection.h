//

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
#include "GameplayTagContainer.h"
#include "ObjectiveInfoCollection.generated.h"

class AObjective;
/**
 * This struct describes an objective of a game mode
 */
USTRUCT(BlueprintType)
struct OBJECTIVESYSTEM_API FObjectiveInfo
{
	GENERATED_BODY()

	//the class of the objective that will be spawned when this objective is setup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	TSubclassOf<AObjective> ObjectiveClass;

	//a descriptor and ID tag for this objective
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	FGameplayTagContainer ObjectiveTags = FGameplayTagContainer();

	//The number of times this objective must be completed to be considered successfully completed
	//if this value is -1, it will be overridden by the value in the objective class
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	int32 SuccessCount = -1;
	
	//The number of times this objective must be failed for this objective to be considered failed
	//A value of zero means that this objective cannot be failed
	//if this value is -1, it will be overridden by the value in the objective class
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	int32 FailureCount = -1;
};

/**
 * This struct describes the current status objective of a game mode
 */
USTRUCT(BlueprintType)
struct OBJECTIVESYSTEM_API FObjectiveStatus
{
	GENERATED_BODY()

	//the assignee that is working on completing the objective
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	AActor* Assignee = nullptr;

	//whether the assignee has started working on this objective
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	bool bHasBegun = false;

	//a descriptor and ID tag for this objective
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	FGameplayTagContainer ObjectiveTags;

	//the class of the objective
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	TSubclassOf<AObjective> ObjectiveClass;

	//The number of times this objective has been completed successfully
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	int32 SuccessCount = 0;
	
	//The number of times this objective has been failed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	int32 FailureCount = 0;
};

UCLASS()
class OBJECTIVESYSTEM_API UObjectiveInfoCollection : public UDataAsset
{
	GENERATED_BODY()

protected:
	//an array of objectives that can be completed by actors in this game mode
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Objective System")
	TArray<FObjectiveInfo> ObjectiveInfoArray;

public:

	UFUNCTION(BlueprintPure, Category = "Objective System")
	TArray<FObjectiveInfo> GetObjectiveInfos() const { return ObjectiveInfoArray; }

	UFUNCTION()
	const FGameplayTagContainer GetAllObjectiveTags() const;
};
