// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIController.h"
#include "GameplayTags.h"
#include "SOCAIBehavior.h"
#include "SOCAIBehaviorManager.h"
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

	FSOCAIAction CurrentActionStruct;
	bool bSuccess = LocalCurrentBehavior->CalculateCurrentControllerAction(this,CurrentActionStruct);

	

}

void ASOCAIController::BeginPlay()
{
	Super::BeginPlay();

	TryCreateBehaviorManager();

	SetBehaviorState(SOCAIBehaviorTags::Idle);
	SetBehaviorState(SOCAIBehaviorTags::FollowSchedule);

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
