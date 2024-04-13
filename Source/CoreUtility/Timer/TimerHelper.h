// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "TimerHelper.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerHelperFinishedDelegate, UTimerHelper*, TimerHelper);

/**
 * 
 */
UCLASS()
class COREUTILITY_API UTimerHelper : public UObject
{
	GENERATED_BODY()

public:
	static UTimerHelper* CreateTimerHelper(UObject* WorldContextObject, float Time, FGameplayTag Tag, FOnTimerHelperFinishedDelegate TimerHelperDelegate, bool bDestroyWhenFinished = true);
	
	void DestroyTimerHelper(UObject* WorldContextObject);

	const FGameplayTag& GetTag() const { return Tag; }
protected:

	UFUNCTION()
	void OnTimerFinished();

	UPROPERTY()
	FGameplayTag Tag;

	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY()
	bool bDestroyWhenFinished;

	FOnTimerHelperFinishedDelegate OnTimerHelperFinishedDelegate;
	
};
