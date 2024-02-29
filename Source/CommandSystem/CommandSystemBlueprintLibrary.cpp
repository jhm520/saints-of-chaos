// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandSystemBlueprintLibrary.h"

#include "Components/CommandComponent.h"
#include "Interfaces/CommandableInterface.h"
#include "Interfaces/CommandInterface.h"

bool UCommandSystemBlueprintLibrary::CommandActor(AActor* CommanderActor, AActor* CommandedActor, const FCommandInfo& Command)
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

FCommandInfo UCommandSystemBlueprintLibrary::MakeCommand(AActor* CommanderActor, const FGameplayTag& CommandTag, AActor* TargetActor, const FVector& TargetLocation)
{
	FCommandInfo Command;
	Command.Commander = CommanderActor;
	Command.CommandTag = CommandTag;
	Command.TargetActor = TargetActor;
	Command.TargetLocation = TargetLocation;
	Command.Guid = FGuid::NewGuid();

	return Command;
}
