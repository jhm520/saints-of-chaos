// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCPlayerState.h"

#include "CoreUtility/CoreUtilityBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "ObjectiveSystem/Components/ObjectiveAssigneeComponent.h"
#include "ObjectiveSystem/Components/ObjectiveTrackerComponent.h"

#pragma region Framework
ASOCPlayerState::ASOCPlayerState()
{
	ObjectiveAssigneeComponent = CreateDefaultSubobject<UObjectiveAssigneeComponent>(TEXT("ObjectiveAssigneeComponent"));

	ObjectiveTrackerComponent = CreateDefaultSubobject<UObjectiveTrackerComponent>(TEXT("ObjectiveTrackerComponent"));
}
UE_DISABLE_OPTIMIZATION
void ASOCPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		PlayerIndex = UCoreUtilityBlueprintLibrary::GetAuthPlayerControllerId(this, Cast<APlayerController>(GetOwner()));
		OnRep_PlayerIndex();
	}

}
UE_ENABLE_OPTIMIZATION
void ASOCPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ASOCPlayerState, PlayerIndex, COND_None, REPNOTIFY_Always);
}
#pragma endregion

#pragma region SOC Player State;
void ASOCPlayerState::SetPlayerIndex(int32 InPlayerIndex)
{
	PlayerIndex = InPlayerIndex;
	OnRep_PlayerIndex();
}

void ASOCPlayerState::OnRep_PlayerIndex()
{
	OnPlayerIndexChanged.Broadcast(this, PlayerIndex);
}

#pragma endregion

