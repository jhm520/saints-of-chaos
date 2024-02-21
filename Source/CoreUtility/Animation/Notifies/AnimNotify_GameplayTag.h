// Fill out your copyright notice in the Description page of Project Settings.

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
