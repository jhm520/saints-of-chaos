// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAIAvatarComponent.h"

#include "Net/UnrealNetwork.h"

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

}

#pragma endregion

#pragma region Action

void USOCAIAvatarComponent::OnRep_CurrentAction(const FSOCAIAction& PreviousAction)
{
	OnActionChanged(CurrentAction, PreviousAction);
}

void USOCAIAvatarComponent::OnActionChanged(const FSOCAIAction& InCurrentAction, const FSOCAIAction& InPreviousAction)
{
	
}

#pragma endregion

