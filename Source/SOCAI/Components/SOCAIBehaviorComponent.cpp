// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehaviorComponent.h"

#include "Kismet/GameplayStatics.h"
#include "SOCAI/Behavior/SOCAIBehavior.h"
#include "SOCAI/Behavior/SOCAIBehaviorManager.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"


// Sets default values for this component's properties
USOCAIBehaviorComponent::USOCAIBehaviorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void USOCAIBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	TryCreateBehaviorManager();

	SetBehaviorState(GetRootBehaviorState());
	// ...
	
}


// Called every frame
void USOCAIBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TickUpdateBehavior(DeltaTime);

	// ...
}
UE_DISABLE_OPTIMIZATION
void USOCAIBehaviorComponent::TickUpdateBehavior(const float DeltaSeconds)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority)
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
	const bool bSuccess = LocalCurrentBehavior->CalculateCurrentAction(GetOwner(), CurrentActionStruct, BehaviorPath);

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("Following Behavior %s, Doing action %s"), *CurrentActionStruct.BehaviorTag.ToString(), *CurrentActionStruct.ActionTag.ToString()));

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

void USOCAIBehaviorComponent::DoAction(const FSOCAIAction& InAction)
{
	//trigger a behavior state change if the action says we're supposed to
	if (InAction.BehaviorTag != SOCAIBehaviorTags::None)
	{
		SetBehaviorState(InAction.BehaviorTag);
	}

	//do any moves, attacks, targetings, spells that are passed in through the SOCAIAction
	
	if (GetOwner()->Implements<USOCAIBehaviorInterface>())
	{
		ISOCAIBehaviorInterface::Execute_DoAIAction(GetOwner(), InAction);
	}
}

void USOCAIBehaviorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

bool USOCAIBehaviorComponent::SetBehaviorState(const FGameplayTag& InBehaviorTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority)
	{
		return false;
	}
	
	const FGameplayTag& PreviousBehaviorState = CurrentBehaviorState;

	CurrentBehaviorState = InBehaviorTag;

	CurrentBehavior = GetBehavior(GetCurrentBehaviorState());
	
	return true;
}


USOCAIBehavior* USOCAIBehaviorComponent::GetBehavior(const FGameplayTag& InBehaviorTag)
{
	ASOCAIBehaviorManager* LocalBehaviorManager = GetBehaviorManager();
	
	if (!IsValid(LocalBehaviorManager))
	{
		return nullptr;
	}

	return BehaviorManager->GetBehavior(InBehaviorTag);
}

bool USOCAIBehaviorComponent::TryCreateBehaviorManager()
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority)
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
UE_ENABLE_OPTIMIZATION
