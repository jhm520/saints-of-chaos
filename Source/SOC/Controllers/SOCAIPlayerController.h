// © 2024 John Henry Miller. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CoreUtility/AutoOwnership/Interfaces/AutoOwnerInterface.h"
#include "SOCAIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API ASOCAIPlayerController : public AAIController, public IAutoOwnerInterface
{
	GENERATED_BODY()

#pragma region Framework
public:
	// Sets default values for this character's properties
	ASOCAIPlayerController();

#pragma endregion

#pragma region Auto Ownership

public:
	virtual UAutoOwnershipComponent* GetAutoOwnershipComponent() const override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAutoOwnershipComponent> AutoOwnershipComponent;

#pragma endregion
	
};
