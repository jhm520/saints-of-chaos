// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCCommand_MoveToLocation.h"

#include "AIController.h"
#include "CommandSystem/Components/CommandableComponent.h"
#include "GameFramework/Character.h"

USOCCommand_MoveToLocation::USOCCommand_MoveToLocation()
{
}

void USOCCommand_MoveToLocation::OnCommandBegin(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
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

	 EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(Command.TargetLocation, 25.0f);

	if (Result == EPathFollowingRequestResult::Type::AlreadyAtGoal || Result == EPathFollowingRequestResult::Type::Failed)
	{
		return;
	}
	
	if (!AIController->ReceiveMoveCompleted.Contains(Commandable, FName("OnMoveCommandCompleted")))
	{
		AIController->ReceiveMoveCompleted.AddDynamic(Commandable, &UCommandableComponent::OnMoveCommandCompleted);
	}
}

void USOCCommand_MoveToLocation::OnCommandFinished(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	Super::OnCommandFinished(Commandable, Command);
}

bool USOCCommand_MoveToLocation::CheckCommandFinished(const UCommandableComponent* Commandable, const FCommandInstance& Command) const
{
	// if (!Commandable)
	// {
	// 	return true;
	// }
	//
	// const FVector& OwnerLocation = Commandable->GetOwner()->GetActorLocation();
	// const FVector& TargetLocation = Command.TargetLocation;
	//
	// const float Distance = FVector::Dist(OwnerLocation, TargetLocation);
	//
	// if (Distance < AcceptanceRadius)
	// {
	// 	return true;
	// }

	return Super::CheckCommandFinished(Commandable, Command);
}