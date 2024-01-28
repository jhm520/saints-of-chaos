// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Include
#include "SOCAIController.h"

#include "Navigation/PathFollowingComponent.h"
#include "SOCAI/Components/SOCAIBehaviorComponent.h"
#pragma endregion

#pragma region Framework
ASOCAIController::ASOCAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BehaviorComponent = CreateDefaultSubobject<USOCAIBehaviorComponent>(TEXT("BehaviorComponent"));
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
UE_DISABLE_OPTIMIZATION
void ASOCAIController::DoAIAction_Implementation(const FSOCAIAction& Action)
{
	if (Action.ActionTag == SOCAIActionTags::MoveToLocation)
	{
		const FVector& CurrentMoveDestination = GetPathFollowingComponent()->GetCurrentTargetLocation();

		if (CurrentMoveDestination != Action.TargetLocation)
		{
			MoveToLocation(Action.TargetLocation, 100.0f);
		}
	}
}
UE_ENABLE_OPTIMIZATION
#pragma endregion
