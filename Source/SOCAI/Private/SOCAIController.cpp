// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIController.h"
#include "GameplayTags.h"
#include "SOCAIBehavior.h"
#include "SOCAIBehaviorManager.h"
#include "Kismet/GameplayStatics.h"

ASOCAIController::ASOCAIController(const FObjectInitializer& ObjectInitializer)
{
	
}

void ASOCAIController::BeginPlay()
{
	Super::BeginPlay();

	TryCreateBehaviorManager();

	SetBehaviorState(SOCAIBehaviorTags::Idle);
}

void ASOCAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
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
