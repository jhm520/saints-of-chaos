// Fill out your copyright notice in the Description page of Project Settings.

#include "SOCAIController.h"

#include "NavigationSystem.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "SOCAI/Components/SOCAIBehaviorComponent.h"

#pragma region Framework
ASOCAIController::ASOCAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	MovementAcceptanceRadius = 50.0f;
}

void ASOCAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ASOCAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASOCAIController::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}
#pragma endregion

#pragma region Behavior Inteface


USOCAIBehaviorComponent* ASOCAIController::GetBehaviorComponent() const
{
	ISOCAIBehaviorInterface* PawnBehaviorInterface = Cast<ISOCAIBehaviorInterface>(GetPawn());
	if (!PawnBehaviorInterface)
	{
		return nullptr;
	}

	return PawnBehaviorInterface->GetBehaviorComponent();
}

void ASOCAIController::DoAIAction_Implementation(const FSOCAIAction& Action)
{
	if (Action.ActionTag == SOCAIActionTags::MoveToLocation)
	{
		const FVector& CurrentMoveDestination = GetPathFollowingComponent()->GetCurrentTargetLocation();
		FVector ProjectedTargetLocation;
		UNavigationSystemV1::K2_ProjectPointToNavigation(this, Action.TargetLocation, ProjectedTargetLocation, nullptr, nullptr);
	
		if (CurrentMoveDestination != ProjectedTargetLocation)
		{
			MoveToLocation(Action.TargetLocation, MovementAcceptanceRadius);
		}
	}

	if (Action.ActionTag == SOCAIActionTags::MoveToActor)
	{
		MoveToActor(Action.TargetActor, MovementAcceptanceRadius);
	}

	if (Action.ActionTag == SOCAIActionTags::Attack)
	{
		SetFocus(Action.TargetActor);
	}

	if (Action.ActionTag == SOCAIActionTags::None)
	{
		ClearFocus(EAIFocusPriority::Gameplay);
	}
}

void ASOCAIController::DoAIAction_MoveToLocation(const FSOCAIAction& Action) const
{
	
}

void ASOCAIController::OnEnteredBehavior_Implementation(const FSOCAIAction& InEnteredBehaviorAction, const FSOCAIAction& InExitedBehaviorAction) const
{
	if (!GetPawn() || !GetPawn()->Implements<USOCAIBehaviorInterface>())
	{
		return;
	}

	ISOCAIBehaviorInterface::Execute_OnEnteredBehavior(GetPawn(), InEnteredBehaviorAction, InExitedBehaviorAction);
}

void ASOCAIController::OnExitedBehavior_Implementation(const FSOCAIAction& InExitedBehaviorAction, const FSOCAIAction& InEnteredBehaviorAction) const
{
	if (!GetPawn() || !GetPawn()->Implements<USOCAIBehaviorInterface>())
	{
		return;
	}

	ISOCAIBehaviorInterface::Execute_OnExitedBehavior(GetPawn(), InExitedBehaviorAction, InEnteredBehaviorAction);
}

#pragma endregion

#pragma region Aggro System
UAggroSystemComponent* ASOCAIController::GetAggroSystemComponent() const
{
	if (!GetPawn())
	{
		return nullptr;
	}

	IAggroInterface* AggroInterface = Cast<IAggroInterface>(GetPawn());

	if (!AggroInterface)
	{
		return nullptr;
	}

	return AggroInterface->GetAggroSystemComponent();
}

bool ASOCAIController::ShouldAggro(AActor* AggroTarget) const
{
	IAggroInterface* AggroInterface = Cast<IAggroInterface>(GetPawn());

	if (!AggroInterface)
	{
		return false;
	}

	return AggroInterface->ShouldAggro(AggroTarget);
}

#pragma endregion


#pragma region Attitude System
EAttitude ASOCAIController::GetAttitudeTowards_Implementation(AActor* Other) const
{
	if (!GetPawn())
	{
		return EAttitude::Neutral;
	}

	if (!GetPawn()->Implements<UAttitudeInterface>())
	{
		return EAttitude::Neutral;
	}

	return IAttitudeInterface::Execute_GetAttitudeTowards(GetPawn(), Other);
}
#pragma endregion

#pragma region Ability System

UAbilitySystemComponent* ASOCAIController::GetAbilitySystemComponent() const
{
	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(GetPawn());

	if (!AbilitySystemInterface)
	{
		return nullptr;
	}

	return AbilitySystemInterface->GetAbilitySystemComponent();
}

#pragma endregion
