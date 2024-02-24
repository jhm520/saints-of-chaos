// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIAvatarComponent.h"

#include "Net/UnrealNetwork.h"
#include "SOCAI/Subsystem/SOCAIBehaviorSubsystem.h"

#pragma region Framework

// Sets default values for this component's properties
USOCAIAvatarComponent::USOCAIAvatarComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void USOCAIAvatarComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void USOCAIAvatarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USOCAIAvatarComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(USOCAIAvatarComponent, CurrentAction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USOCAIAvatarComponent, DirectorPawn, COND_None, REPNOTIFY_Always);
}

#pragma endregion

#pragma region Action

void USOCAIAvatarComponent::SetCurrentAction(const FSOCAIAction& InAction)
{
	const FSOCAIAction PreviousAction = CurrentAction;
	
	CurrentAction = InAction;
	
	OnRep_CurrentAction(PreviousAction);
}

void USOCAIAvatarComponent::OnRep_CurrentAction(const FSOCAIAction& PreviousAction)
{
	OnActionChanged(CurrentAction, PreviousAction);
}

void USOCAIAvatarComponent::OnActionChanged(const FSOCAIAction& InCurrentAction, const FSOCAIAction& InPreviousAction)
{
	USOCAIBehaviorSubsystem* BehaviorSubsystem = USOCAIBehaviorSubsystem::Get(this);
	
	if (!BehaviorSubsystem)
	{
		return;
	}
	
	USOCAIBehavior* CurrentBehavior = BehaviorSubsystem->GetBehavior(InCurrentAction.BehaviorTag);
	USOCAIBehavior* PreviousBehavior = BehaviorSubsystem->GetBehavior(InPreviousAction.BehaviorTag);

	if (PreviousBehavior)
	{
		PreviousBehavior->OnExitedBehavior(GetOwner(), InPreviousAction, InCurrentAction);
	}
	
	if (CurrentBehavior)
	{
		CurrentBehavior->OnEnteredBehavior(GetOwner(), InCurrentAction, InPreviousAction);
	}
}

#pragma endregion

#pragma region Director Pawn

void USOCAIAvatarComponent::SetDirectorPawn(APawn* InDirectorPawn)
{
	DirectorPawn = InDirectorPawn;
	OnRep_DirectorPawn();
}

APawn* USOCAIAvatarComponent::GetDirectorPawn()
{
	return DirectorPawn;
}

void USOCAIAvatarComponent::OnRep_DirectorPawn()
{
	
}

#pragma endregion

