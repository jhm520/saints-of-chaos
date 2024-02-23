// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSUtility/Pawns/RTSPlayerPawn.h"
#include "SelectionSystem/Interfaces/SelectorInterface.h"
#include "SOCRTSPlayerPawn.generated.h"

class USelectorComponent;
/**
 * 
 */
UCLASS()
class SOC_API ASOCRTSPlayerPawn : public ARTSPlayerPawn, public ISelectorInterface
{
	GENERATED_BODY()
#pragma region Framework
public:
	// Sets default values for this pawn's properties
	ASOCRTSPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma endregion

#pragma region Selection System

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Selection")
	TObjectPtr<USelectorComponent> SelectorComponent;

public:

	virtual USelectorComponent* GetSelectorComponent() const override{return SelectorComponent;};

#pragma endregion

};
