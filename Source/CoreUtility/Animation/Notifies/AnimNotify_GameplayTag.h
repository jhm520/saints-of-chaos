// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_GameplayTag.generated.h"

/**
 * 
 */
UCLASS()
class COREUTILITY_API UAnimNotify_GameplayTag : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTag")
	FGameplayTag GameplayTag;
	
};
