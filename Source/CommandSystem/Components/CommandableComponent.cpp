// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandableComponent.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "CommandSystem/Interfaces/CommandableInterface.h"
#include "CommandSystem/CommandInfo.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

#pragma region Framework
UE_DISABLE_OPTIMIZATION
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

	if (GetCurrentCommand().IsValid())
	{
		const bool bCommandFinished = CheckCommandFinished(GetCurrentCommand());

		if (bCommandFinished)
		{
			FinishCurrentCommand();
		}
	}
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

bool UCommandableComponent::GiveCommand(const FCommandInstance& Command)
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

void UCommandableComponent::FinishCurrentCommand()
{
	if (!GetCurrentCommand().IsValid())
	{
		return;
	}

	DequeueCommand();
}


void UCommandableComponent::QueueCommand(const FCommandInstance& Command)
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	const TArray<FCommandInstance> OldCommandQueue = CommandQueue;
	CommandQueue.Add(Command);
	OnRep_CommandQueue(OldCommandQueue);
}

void UCommandableComponent::DequeueCommand()
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	
	const FCommandInstance PreviousCommand = CurrentCommand;
	
	if (CommandQueue.Num() > 0)
	{
		CurrentCommand = CommandQueue[0];
	}
	else
	{
		CurrentCommand = FCommandInstance();
	}
	
	OnRep_CurrentCommand(PreviousCommand);

	const TArray<FCommandInstance> OldCommandQueue = CommandQueue;
	if (CommandQueue.Num() > 0)
	{
		CommandQueue.RemoveAt(0);
	}
	OnRep_CommandQueue(OldCommandQueue);
}


void UCommandableComponent::OnRep_CurrentCommand(const FCommandInstance& PreviousCommand)
{
	if (PreviousCommand.IsValid())
	{
		OnCommandFinished(PreviousCommand);
	}
	
	if (CurrentCommand.IsValid())
	{
		OnCommandBegin(CurrentCommand);
	}
}

void UCommandableComponent::OnRep_CommandQueue(const TArray<FCommandInstance>& OldCommandQueue)
{
	for (const FCommandInstance& Command : CommandQueue)
	{
		if (!OldCommandQueue.Contains(Command))
		{
			OnCommandReceived(Command);
		}
	}
}

void UCommandableComponent::OnCommandReceived(const FCommandInstance& Command)
{
	K2_OnCommandReceived(Command);
}

void UCommandableComponent::OnCommandBegin(const FCommandInstance& Command)
{
	K2_OnCommandBegin(Command);
	
	if (Command.CommandInfo)
	{
		Command.CommandInfo->OnCommandBegin(this, Command);
	}
	
	if (GetOwner() && GetOwner()->Implements<UCommandableInterface>())
	{
		ICommandableInterface::Execute_OnCommandBegin(GetOwner(), Command);
	}
}

void UCommandableComponent::OnCommandFinished(const FCommandInstance& Command)
{
	K2_OnCommandFinished(Command);
}

bool UCommandableComponent::CheckCommandFinished(const FCommandInstance& Command) const
{
	if (Command.IsValid())
	{
		return Command.CommandInfo->CheckCommandFinished(this, Command);
	}
	
	return false;
}

#pragma endregion

#pragma region Command: Movement

void UCommandableComponent::OnMoveCommandCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	ACharacter* CharacterOwner = Cast<ACharacter>(GetOwner());

	if (!CharacterOwner)
	{
		return;
	}

	AAIController* AIController = Cast<AAIController>(CharacterOwner->GetController());

	if (!AIController)
	{
		return;
	}
	
	AIController->ReceiveMoveCompleted.RemoveDynamic(this, &UCommandableComponent::OnMoveCommandCompleted);
	
	FinishCurrentCommand();
}

#pragma endregion

UE_ENABLE_OPTIMIZATION