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
	if (!Other)
	{
		return EAttitude::Neutral;
	}

	USOCAIBehaviorComponent* LocalBehaviorComponent = GetBehaviorComponent();

	if (!LocalBehaviorComponent)
	{
		return EAttitude::Neutral;
	}

	AActor* Director = LocalBehaviorComponent->GetDirector();

	if (!Director)
	{
		return EAttitude::Neutral;
	}

	ISOCAIBehaviorInterface* OtherBehaviorInterface = Cast<ISOCAIBehaviorInterface>(Other);

	if (!OtherBehaviorInterface)
	{
		return EAttitude::Neutral;
	}
	
	USOCAIBehaviorComponent* OtherBehaviorComponent = OtherBehaviorInterface->GetBehaviorComponent();

	if (!OtherBehaviorComponent)
	{
		return EAttitude::Neutral;
	}

	AActor* OtherDirector = OtherBehaviorComponent->GetDirector();

	if (!OtherDirector)
	{
		return EAttitude::Neutral;
	}

	if (Director == OtherDirector)
	{
		return EAttitude::Friendly;
	}

	return EAttitude::Hostile;
}
#pragma endregion
