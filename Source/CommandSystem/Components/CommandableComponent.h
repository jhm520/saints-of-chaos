// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "CommandSystem/CommandSystemBlueprintLibrary.h"
#include "CommandableComponent.generated.h"

//this is a component that is meant to be added to actors that are selectable by selectors
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMMANDSYSTEM_API UCommandableComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class UCommandComponent;
#pragma region Framework

public:	
	// Sets default values for this component's properties
	UCommandableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion

#pragma region Command
public:
	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "Command")
	bool GiveCommand(const FCommandInstance& Command, bool bQueue = false);

	UFUNCTION(BlueprintPure, Category = "Command")
	const FCommandInstance& GetCurrentCommand() const { return CurrentCommand; }

protected:
	void FinishCurrentCommand();

	void QueueCommand(const FCommandInstance& Command);

	void SetCurrentCommand(const FCommandInstance& Command);
	
	void DequeueCommand();

	void ClearCurrentCommand();
	
	void ClearCommandQueue();
	
	void ClearMovementCommand();

	AAIController* GetAIController();

	//the current command that this commandable actor is carrying out
	UPROPERTY(Transient, ReplicatedUsing = "OnRep_CurrentCommand")
	FCommandInstance CurrentCommand;
	
	UFUNCTION()
	void OnRep_CurrentCommand(const FCommandInstance& PreviousCommand);
	
	//a list of commands that will be executed in order
	UPROPERTY(Transient, ReplicatedUsing = "OnRep_CommandQueue")
	TArray<FCommandInstance> CommandQueue;

	UFUNCTION()
	void OnRep_CommandQueue(const TArray<FCommandInstance>& OldCommandQueue);
	
	void OnCommandReceived(const FCommandInstance& Command);
	
	void OnCommandBegin(const FCommandInstance& Command);
	
	void OnCommandFinished(const FCommandInstance& Command);

	bool CheckCommandFinished(const FCommandInstance& Command) const;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnCommandReceived"), Category = "Command")
	void K2_OnCommandReceived(const FCommandInstance& Command);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnCommandBegin"), Category = "Command")
	void K2_OnCommandBegin(const FCommandInstance& Command);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnCommandFinished"), Category = "Command")
	void K2_OnCommandFinished(const FCommandInstance& Command);

#pragma endregion

#pragma region Command: Movement
public:
	UFUNCTION()
	void OnMoveCommandCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

#pragma endregion

};
