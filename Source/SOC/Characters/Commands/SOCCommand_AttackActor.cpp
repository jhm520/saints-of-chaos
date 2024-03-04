// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCCommand_AttackActor.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "CommandSystem/Components/CommandableComponent.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"

USOCCommand_AttackActor::USOCCommand_AttackActor()
{
}

void USOCCommand_AttackActor::OnCommandBegin(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	Super::OnCommandBegin(Commandable, Command);

	if (!Commandable)
	{
		return;
	}

	ACharacter* CharacterOwner = Cast<ACharacter>(Commandable->GetOwner());

	if (!CharacterOwner)
	{
		return;
	}

	AAIController* AIController = Cast<AAIController>(CharacterOwner->GetController());

	if (!AIController)
	{
		return;
	}

	 EPathFollowingRequestResult::Type Result = AIController->MoveToActor(Command.TargetActor, 25.0f);
}

void USOCCommand_AttackActor::OnCommandFinished(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	Super::OnCommandFinished(Commandable, Command);
}

void USOCCommand_AttackActor::ContinueCommand(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	Super::ContinueCommand(Commandable, Command);
}

bool USOCCommand_AttackActor::CheckCommandFinished(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	if (!Commandable)
	{
		return true;
	}

	if (!Command.IsValid())
	{
		return true;
	}

	//if the target actor is no longer valid, the command is finished
	if (!Command.TargetActor)
	{
		return true;
	}

	//TODO: Check if the target actor is dead, return true if it is

	return Super::CheckCommandFinished(Commandable, Command);
}