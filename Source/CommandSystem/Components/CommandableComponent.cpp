// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandableComponent.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"

#pragma region Framework

// Sets default values for this component's properties
UCommandableComponent::UCommandableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	SetIsReplicatedByDefault(true);

	// ...
}

// Called when the game starts
void UCommandableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UCommandableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCommandableComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UCommandableComponent, CurrentCommand, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCommandableComponent, CommandQueue, COND_None, REPNOTIFY_Always);
}
#pragma endregion

#pragma region Command

bool UCommandableComponent::GiveCommand(const FCommandInfo& Command)
{
	if (!GetOwner()->HasAuthority())
	{
		return false;
	}

	QueueCommand(Command);

	if (!CurrentCommand.IsValid())
	{
		DequeueCommand();
	}
	
	return true;
}

void UCommandableComponent::QueueCommand(const FCommandInfo& Command)
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	const TArray<FCommandInfo> OldCommandQueue = CommandQueue;
	CommandQueue.Add(Command);
	OnRep_CommandQueue(OldCommandQueue);
}

void UCommandableComponent::DequeueCommand()
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	
	const FCommandInfo PreviousCommand = CurrentCommand;
	CurrentCommand = CommandQueue[0];
	OnRep_CurrentCommand(PreviousCommand);

	const TArray<FCommandInfo> OldCommandQueue = CommandQueue;
	CommandQueue.RemoveAt(0);
	OnRep_CommandQueue(OldCommandQueue);
}


void UCommandableComponent::OnRep_CurrentCommand(const FCommandInfo& PreviousCommand)
{
	
}

void UCommandableComponent::OnRep_CommandQueue(const TArray<FCommandInfo>& OldCommandQueue)
{
	
}

#pragma endregion