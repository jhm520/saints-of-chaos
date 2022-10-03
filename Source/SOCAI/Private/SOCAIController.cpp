// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIController.h"
#include "GameplayTags.h"
#include "SOCAIBehavior.h"

ASOCAIController::ASOCAIController(const FObjectInitializer& ObjectInitializer)
{
	
}

void ASOCAIController::BeginPlay()
{
	Super::BeginPlay();

	TryCreateMainBehavior();

	SetBehaviorState(SOCAIBehaviorTags::Idle);
}

void ASOCAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	TryDestroyMainBehavior();
}

bool ASOCAIController::SetBehaviorState(const FGameplayTag& InBehaviorTag)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		return false;
	}
	
	const FGameplayTag& PreviousBehaviorState = CurrentBehaviorState;

	CurrentBehaviorState = InBehaviorTag;
	
	return true;
}

bool ASOCAIController::TryCreateMainBehavior()
{
	if (GetLocalRole() != ROLE_Authority)
	{
		return false;
	}
	
	if (MainBehavior)
	{
		return false;
	}

	MainBehavior = NewObject<USOCAIBehavior>(this, MainBehaviorClass, FName(TEXT("Main Behavior")));

	return true;
}

bool ASOCAIController::TryDestroyMainBehavior()
{
	if (GetLocalRole() != ROLE_Authority)
	{
		return false;
	}

	for(FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		ASOCAIController* Controller = Cast<ASOCAIController>(Iterator->Get());

		//Found a controller other than this one
		if (Controller != this)
		{
			return false;
		}
	}
	//didn't find a controller other than this one, destroy
	MainBehavior->ConditionalBeginDestroy();
	return true;

}
