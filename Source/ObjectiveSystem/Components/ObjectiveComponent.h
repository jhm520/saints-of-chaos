// Copyright [2022] Psychedelic Games. All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectiveComponent.generated.h"

class AObjective;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OBJECTIVESYSTEM_API UObjectiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectiveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region Objective System

public:
	UFUNCTION(BlueprintPure, Category = "Objective System")
	AObjective* GetObjective() const {return Objective;};

	UFUNCTION(BlueprintCallable, Category = "Objective System")
	void SetObjective(AObjective* InObjective) {Objective = InObjective;};

protected:
	UPROPERTY()
	TObjectPtr<AObjective> Objective;

#pragma endregion
	
};
