// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandSystemBlueprintLibrary.h"

#include "CommandSubsystem.h"
#include "Components/CommandableComponent.h"
#include "Components/CommandComponent.h"
#include "Interfaces/CommandableInterface.h"
#include "Interfaces/CommandInterface.h"

bool UCommandSystemBlueprintLibrary::CommandActor(AActor* CommanderActor, AActor* CommandedActor, const FCommandInstance& Command)
{
	ICommandInterface * CommandInterface = Cast<ICommandInterface>(CommanderActor);

	if (!CommandInterface)
	{
		return false;
	}

	UCommandComponent* CommandComponent = CommandInterface->GetCommandComponent();

	if (!CommandComponent)
	{
		return false;
	}

	ICommandableInterface* CommandableInterface = Cast<ICommandableInterface>(CommandedActor);

	if (!CommandableInterface)
	{
		return false;
	}

	UCommandableComponent* CommandableComponent = CommandableInterface->GetCommandableComponent();

	if (!CommandableComponent)
	{
		return false;
	}

	return CommandComponent->Command(CommandableComponent, Command);
}

FCommandInstance UCommandSystemBlueprintLibrary::MakeCommand(AActor* CommanderActor, const FGameplayTag& CommandTag, AActor* TargetActor, const FVector& TargetLocation)
{
	FCommandInstance Command;
	Command.Commander = CommanderActor;

	UCommandSubsystem* CommandSubsystem = UCommandSubsystem::Get(CommanderActor);

	if (CommandSubsystem)
	{
		Command.CommandInfo = CommandSubsystem->GetCommand(CommandTag);
	}
	
	Command.TargetActor = TargetActor;
	Command.TargetLocation = TargetLocation;
	Command.Guid = FGuid::NewGuid();

	return Command;
}

void UCommandSystemBlueprintLibrary::GetCurrentCommand(const AActor* CommandableActor, FCommandInstance& OutCommand)
{
	const ICommandableInterface* CommandableInterface = Cast<ICommandableInterface>(CommandableActor);

	if (!CommandableInterface)
	{
		return;
	}

	const UCommandableComponent* CommandableComponent = CommandableInterface->GetCommandableComponent();

	if (!CommandableComponent)
	{
		return;
	}

	OutCommand = CommandableComponent->GetCurrentCommand();
}
