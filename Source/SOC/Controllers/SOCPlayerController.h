// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreUtility/AutoOwnership/Components/AutoOwnershipComponent.h"
#include "GameFramework/PlayerController.h"
#include "SOCPlayerController.generated.h"

class UAutoOwnershipComponent;

/**
 * 
 */

UCLASS()
class SOC_API ASOCPlayerController : public APlayerController
{
	GENERATED_BODY()
#pragma region Framework
public:
	// Sets default values for this character's properties
	ASOCPlayerController();
#pragma endregion

#pragma region Auto Ownership
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAutoOwnershipComponent> AutoOwnershipComponent;

#pragma endregion

};
