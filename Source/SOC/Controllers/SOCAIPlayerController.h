// © 2024 John Henry Miller. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CoreUtility/AutoOwnership/Interfaces/AutoOwnerInterface.h"
#include "ObjectiveSystem/Interfaces/ObjectiveAssigneeInterface.h"
#include "SOCAIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API ASOCAIPlayerController : public AAIController, public IAutoOwnerInterface, public IObjectiveAssigneeInterface
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

#pragma region Objective System
public:
	virtual UObjectiveAssigneeComponent* GetObjectiveAssigneeComponent() const override;

	virtual AActor* GetAssignee() override;

#pragma endregion

	
};
