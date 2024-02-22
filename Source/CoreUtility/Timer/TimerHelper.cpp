// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerHelper.h"

UTimerHelper* UTimerHelper::CreateTimerHelper(UObject* WorldContextObject, float Time, FGameplayTag Tag, FOnTimerHelperFinishedDelegate TimerHelperDelegate, bool bDestroyWhenFinished)
{
	if (!WorldContextObject)
	{
		return nullptr;
	}

	UWorld* World = WorldContextObject->GetWorld();

	if (!World)
	{
		return nullptr;
	}

	UTimerHelper* TimerHelper = NewObject<UTimerHelper>(WorldContextObject);

	if (!TimerHelper)
	{
		return nullptr;
	}

	TimerHelper->Tag = Tag;
	TimerHelper->bDestroyWhenFinished = bDestroyWhenFinished;
	TimerHelper->OnTimerHelperFinishedDelegate = TimerHelperDelegate;

	World->GetTimerManager().SetTimer(TimerHelper->TimerHandle, TimerHelper, &UTimerHelper::OnTimerFinished, Time, false);
	
	return TimerHelper;
}

void UTimerHelper::DestroyTimerHelper(UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		return;
	}

	UWorld* World = WorldContextObject->GetWorld();

	if (!World)
	{
		return;
	}

	OnTimerHelperFinishedDelegate.RemoveAll(GetOuter());
	
	World->GetTimerManager().ClearTimer(TimerHandle);

	ConditionalBeginDestroy();
}


void UTimerHelper::OnTimerFinished()
{
	OnTimerHelperFinishedDelegate.Broadcast(this);

	if (bDestroyWhenFinished)
	{
		this->ConditionalBeginDestroy();
	}
}