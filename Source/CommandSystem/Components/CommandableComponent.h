// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "CommandableComponent.generated.h"

//struct to represent an AIController's current action
USTRUCT(BlueprintType)
struct COMMANDSYSTEM_API FCommandInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	AActor* Commander = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	FGameplayTag CommandTag = FGameplayTag::EmptyTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	AActor* TargetActor = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	FVector TargetLocation = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	FGuid Guid = FGuid();

	bool IsValid() const
	{
		return Commander != nullptr && CommandTag.IsValid();
	}

	friend bool operator==(const FCommandInfo& A, const FCommandInfo& B)
	{
		return A.Guid == B.Guid;
	}
	
	FCommandInfo(){}
};

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
	bool GiveCommand(const FCommandInfo& Command);

	UFUNCTION(BlueprintPure, Category = "Command")
	const FCommandInfo& GetCurrentCommand() const { return CurrentCommand; }

protected:

	void QueueCommand(const FCommandInfo& Command);
	
	void DequeueCommand();

	//the current command that this commandable actor is carrying out
	UPROPERTY(Transient, ReplicatedUsing = "OnRep_CurrentCommand")
	FCommandInfo CurrentCommand;
	
	UFUNCTION()
	void OnRep_CurrentCommand(const FCommandInfo& PreviousCommand);
	
	//a list of commands that will be executed in order
	UPROPERTY(Transient, ReplicatedUsing = "OnRep_CommandQueue")
	TArray<FCommandInfo> CommandQueue;

	UFUNCTION()
	void OnRep_CommandQueue(const TArray<FCommandInfo>& OldCommandQueue);
	
	void OnCommandReceived(const FCommandInfo& Command);
	
	void OnCommandBegin(const FCommandInfo& Command);
	
	void OnCommandFinished(const FCommandInfo& Command);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnCommandReceived"), Category = "Command")
	void K2_OnCommandReceived(const FCommandInfo& Command);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnCommandBegin"), Category = "Command")
	void K2_OnCommandBegin(const FCommandInfo& Command);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnCommandFinished"), Category = "Command")
	void K2_OnCommandFinished(const FCommandInfo& Command);

#pragma endregion

};
