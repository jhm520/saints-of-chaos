// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "EnhancedInputActionBindingCollection.generated.h"

UENUM(BlueprintType)
enum class EInputActionBinding : uint8
{
	None UMETA(DisplayName = "None"),
	Movement UMETA(DisplayName = "Movement"),
	CameraZoom UMETA(DisplayName = "CameraZoom")
	
	// Add your own bindings if you need to.
};

USTRUCT(BlueprintType)
struct FEnhancedInputActionBinding
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	TObjectPtr<const UInputAction> InputAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	EInputActionBinding InputActionBinding;

	FEnhancedInputActionBinding()
	{
		InputAction = nullptr;
		InputActionBinding = EInputActionBinding::None;
	}
};

/**
 * 
 */
UCLASS(Blueprintable)
class COREUTILITY_API UEnhancedInputActionBindingCollection : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FEnhancedInputActionBinding> InputActionBindings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputContext;
};
