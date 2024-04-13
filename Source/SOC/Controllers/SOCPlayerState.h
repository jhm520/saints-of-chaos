// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "CoreUtility/Sorting/Interface/SortableInterface.h"
#include "GameFramework/PlayerState.h"
#include "ObjectiveSystem/Interfaces/ObjectiveAssigneeInterface.h"
#include "ObjectiveSystem/Interfaces/ObjectiveTrackerInterface.h"
#include "SOCPlayerState.generated.h"

class UObjectiveTrackerComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerIndexChangedDelegate, APlayerState*, PlayerState, int32, PlayerIndex);

/**
 * 
 */
UCLASS()
class SOC_API ASOCPlayerState : public APlayerState, public IObjectiveAssigneeInterface, public IObjectiveTrackerInterface, public ISortableInterface
{
	GENERATED_BODY()

	friend class ASOCPlayerController;
#pragma region Framework
	ASOCPlayerState();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
#pragma endregion

#pragma region SOC Player State;
protected:
	void SetPlayerIndex(int32 InPlayerIndex);
	
	UPROPERTY(ReplicatedUsing="OnRep_PlayerIndex", Transient, BlueprintReadOnly, Category = "SOC Player State")
	int32 PlayerIndex = -1;

	UFUNCTION()
	void OnRep_PlayerIndex();

	UPROPERTY(BlueprintAssignable, Category = "SOC Player State")
	FOnPlayerIndexChangedDelegate OnPlayerIndexChanged;
	
#pragma endregion

#pragma region Objective System
public:
	virtual UObjectiveAssigneeComponent* GetObjectiveAssigneeComponent() const override {return ObjectiveAssigneeComponent;}

	// Getter function for the ObjectiveAssigneeComponent variable
	UFUNCTION()
	virtual AActor* GetAssignee() override {return this;}
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	UObjectiveAssigneeComponent* ObjectiveAssigneeComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Objective System")
	UObjectiveTrackerComponent* ObjectiveTrackerComponent;
	
	virtual UObjectiveTrackerComponent* GetObjectiveTrackerComponent() const override {return ObjectiveTrackerComponent;}

#pragma endregion

#pragma region Sortable

	virtual bool Compare(const AActor* OtherActor, FGameplayTag SortTag, bool bDescending) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sorting")
	FGameplayTag PlayerIndexSortTag;

#pragma endregion

};
