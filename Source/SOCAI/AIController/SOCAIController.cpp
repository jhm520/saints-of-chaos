// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIController.h"
#include "GameplayTags.h"
#include "SOCAI/Behavior/SOCAIBehavior.h"
#include "SOCAI/Behavior/SOCAIBehaviorManager.h"
#include "Kismet/GameplayStatics.h"

ASOCAIController::ASOCAIController(const FObjectInitializer& ObjectInitializer)
{
	
}

void ASOCAIController::TickUpdateBehavior(const float DeltaSeconds)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	
	const USOCAIBehavior* LocalCurrentBehavior = GetCurrentBehavior();

	if (!IsValid(LocalCurrentBehavior))
	{
		return;
	}

	//Have the current behavior object figure out what this controller is supposed to do at this moment
	FSOCAIAction CurrentActionStruct = FSOCAIAction();
	FGameplayTagContainer BehaviorPath = FGameplayTagContainer::EmptyContainer;
	const bool bSuccess = LocalCurrentBehavior->CalculateCurrentControllerAction(this,CurrentActionStruct, BehaviorPath);

	//do the action
	if (bSuccess)
	{
		DoAction(CurrentActionStruct);
	}
	else
	{
		//return to root behavior
		SetBehaviorState(GetRootBehaviorState());
	}
}

void ASOCAIController::DoAction_Implementation(const FSOCAIAction& InAction)
{
	//trigger a behavior state change if the action says we're supposed to
	if (InAction.BehaviorTag != SOCAIBehaviorTags::None)
	{
		SetBehaviorState(InAction.BehaviorTag);
	}

	//do any moves, attacks, targetings, spells that are passed in through the SOCAIAction
	
}

void ASOCAIController::BeginPlay()
{
	Super::BeginPlay();

	TryCreateBehaviorManager();

	SetBehaviorState(GetRootBehaviorState());

}

void ASOCAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASOCAIController::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TickUpdateBehavior(DeltaSeconds);
	
}

bool ASOCAIController::SetBehaviorState(const FGameplayTag& InBehaviorTag)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		return false;
	}
	
	const FGameplayTag& PreviousBehaviorState = CurrentBehaviorState;

	CurrentBehaviorState = InBehaviorTag;

	CurrentBehavior = GetBehavior(GetCurrentBehaviorState());
	
	return true;
}


USOCAIBehavior* ASOCAIController::GetBehavior(const FGameplayTag& InBehaviorTag)
{
	ASOCAIBehaviorManager* LocalBehaviorManager = GetBehaviorManager();
	
	if (!IsValid(LocalBehaviorManager))
	{
		return nullptr;
	}

	return BehaviorManager->GetBehavior(InBehaviorTag);
}

bool ASOCAIController::TryCreateBehaviorManager()
{
	if (GetLocalRole() != ROLE_Authority)
	{
		return false;
	}
	
	if (GetBehaviorManager())
	{
		return false;
	}

	TArray<AActor*> BehaviorManagers;
	UGameplayStatics::GetAllActorsOfClass(this, ASOCAIBehaviorManager::StaticClass(),BehaviorManagers);

	if (BehaviorManagers.Num() > 0)
	{
		BehaviorManager = Cast<ASOCAIBehaviorManager>(BehaviorManagers[0]);
	}
	else
	{
		BehaviorManager = GetWorld()->SpawnActor<ASOCAIBehaviorManager>(BehaviorManagerClass);
	}

	return true;
}
