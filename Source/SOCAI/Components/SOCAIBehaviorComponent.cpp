// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIBehaviorComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "SOCAI/Behavior/SOCAIBehavior.h"
#include "SOCAI/Behavior/SOCAIBehaviorManager.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "SOCAI/Components/SOCAIAvatarComponent.h"

#pragma region Framework

// Sets default values for this component's properties
USOCAIBehaviorComponent::USOCAIBehaviorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//SetIsReplicatedByDefault(true);
	// ...
	
	CurrentAction = FSOCAIAction();
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
#pragma endregion

#pragma region Behavior

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

	//GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Red, FString::Printf(TEXT("Following Behavior %s, Doing action %s"), *CurrentActionStruct.BehaviorTag.ToString(), *CurrentActionStruct.ActionTag.ToString()));

	//do the action
	if (bSuccess)
	{
		DoAction(CurrentActionStruct);
	}
	else
	{
		//return to root behavior
	}

	//TODO: figure out more elegant way to reset the behavior state to the root of the tree
	SetBehaviorState(GetRootBehaviorState());

}

void USOCAIBehaviorComponent::OnBehaviorChanged(const FSOCAIAction& InCurrentAction, const FSOCAIAction& InPreviousAction)
{
	USOCAIBehavior* PreviousActionBehavior = GetBehavior(InPreviousAction.BehaviorTag);
	
	if (PreviousActionBehavior)
	{
		PreviousActionBehavior->OnExitedBehavior(GetOwner(), InPreviousAction, InCurrentAction);
	}

	USOCAIBehavior* CurrentActionBehavior = GetBehavior(InCurrentAction.BehaviorTag);
	
	if (CurrentActionBehavior)
	{
		CurrentActionBehavior->OnEnteredBehavior(GetOwner(), InCurrentAction, InPreviousAction);
	}
}

void USOCAIBehaviorComponent::OnActionChanged(const FSOCAIAction& InCurrentAction, const FSOCAIAction& InPreviousAction)
{
	if (GetOwner()->Implements<USOCAIBehaviorInterface>())
	{
		ISOCAIBehaviorInterface::Execute_DoAIAction(GetOwner(), InCurrentAction);
	}
	
	//replicate the action to the avatar component
	ISOCAIBehaviorInterface* BehaviorInterface = Cast<ISOCAIBehaviorInterface>(GetOwner());

	if (!BehaviorInterface)
	{
		return;
	}
	
	USOCAIAvatarComponent* AvatarComponent = BehaviorInterface->GetAvatarComponent();

	if (!AvatarComponent)
	{
		return;
	}

	AvatarComponent->SetCurrentAction(InCurrentAction);
}


void USOCAIBehaviorComponent::DoAction(const FSOCAIAction& InAction)
{
	const FSOCAIAction PreviousAction = CurrentAction;

	CurrentAction = InAction;
	
	//trigger a behavior state change if the action says we're supposed to
	if (InAction.BehaviorTag != SOCAIBehaviorTags::None)
	{
		SetBehaviorState(InAction.BehaviorTag);
	}

	if (PreviousAction.BehaviorTag != CurrentAction.BehaviorTag)
	{
		OnBehaviorChanged(CurrentAction, PreviousAction);
	}

	//do any moves, attacks, targetings, spells that are passed in through the SOCAIAction

	if (CurrentAction != PreviousAction)
	{
		OnActionChanged(CurrentAction, PreviousAction);
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

	USOCAIBehavior* PreviousBehavior = GetBehavior(PreviousBehaviorState);

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
	UGameplayStatics::GetAllActorsOfClass(this, BehaviorManagerClass,BehaviorManagers);

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

#pragma endregion

#pragma region Director

//returns the actor that is directing the behavior of this actor
APawn* USOCAIBehaviorComponent::GetDirectorPawn() const
{
	//replicate the action to the avatar component
	ISOCAIBehaviorInterface* BehaviorInterface = Cast<ISOCAIBehaviorInterface>(GetOwner());

	if (!BehaviorInterface)
	{
		return nullptr;
	}
	
	USOCAIAvatarComponent* AvatarComponent = BehaviorInterface->GetAvatarComponent();

	if (!AvatarComponent)
	{
		return nullptr;
	}
	
	return AvatarComponent->GetDirectorPawn();
}

//sets the actor that directs the behavior of this actor
void USOCAIBehaviorComponent::SetDirectorPawn(APawn* InDirectorPawn)
{
	//replicate the action to the avatar component
	ISOCAIBehaviorInterface* BehaviorInterface = Cast<ISOCAIBehaviorInterface>(GetOwner());

	if (!BehaviorInterface)
	{
		return;
	}
	
	USOCAIAvatarComponent* AvatarComponent = BehaviorInterface->GetAvatarComponent();

	if (!AvatarComponent)
	{
		return;
	}
	
	AvatarComponent->SetDirectorPawn(InDirectorPawn);
}

#pragma endregion
