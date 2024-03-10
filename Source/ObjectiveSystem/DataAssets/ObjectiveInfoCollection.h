// Copyright [2022] Psychedelic Games. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
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
};

/**
 * This struct describes the current status objective of a game mode
 */
USTRUCT(BlueprintType)
struct OBJECTIVESYSTEM_API FObjectiveStatus
{
	GENERATED_BODY()

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
};
