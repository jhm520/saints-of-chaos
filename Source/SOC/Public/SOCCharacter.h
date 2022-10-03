// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ALSXTCharacter.h"
#include "SOCCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API ASOCCharacter : public AALSXTCharacter
{
	GENERATED_BODY()
public:
	void SetupGameplayTags();
	
};
