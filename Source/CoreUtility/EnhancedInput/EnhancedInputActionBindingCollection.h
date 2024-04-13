// © 2024 John Henry Miller. All rights reserved
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
	CameraZoom UMETA(DisplayName = "CameraZoom"),
	Selection UMETA(DisplayName = "Selection"),
	ContextCommand UMETA(DisplayName = "ContextCommand"),
	Modifier_Shift UMETA(DisplayName = "Modifier Shift"),
	ContextCommand_Queue UMETA(DisplayName = "ContextCommand_Queue")
	
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
