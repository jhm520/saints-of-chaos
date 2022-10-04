// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SOCCharacter.generated.h"

/**
 * 
 */
//Base class for characters
UCLASS()
class SOC_API ASOCCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	void SetupGameplayTags();
	
};
