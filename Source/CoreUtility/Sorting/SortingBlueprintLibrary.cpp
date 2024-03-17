// Fill out your copyright notice in the Description page of Project Settings.


#include "SortingBlueprintLibrary.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Interface/SortableInterface.h"


void USortingBlueprintLibrary::SortActorArray(const UObject* WorldContextObject, const FGameplayTag SortTag, const TArray<AActor*>& InArray, TArray<AActor*>& OutArray, bool bDescending /*= true*/)
{
	OutArray = InArray;
	
	OutArray.Sort([&SortTag, &bDescending](const AActor& A, const AActor& B)
	{
		const ISortableInterface* SortableA = Cast<ISortableInterface>(&A);
		const ISortableInterface* SortableB = Cast<ISortableInterface>(&B);

		if (SortableA && SortableB)
		{
			return SortableA->Compare(&B, SortTag, bDescending);
		}
		else
		{
			return false;
		}
	});
}

