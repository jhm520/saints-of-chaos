// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Include
#include "SOCAIController.h"
#include "SOCAI/Components/SOCAIBehaviorComponent.h"
#pragma endregion

#pragma region Framework
ASOCAIController::ASOCAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BehaviorComponent = CreateDefaultSubobject<USOCAIBehaviorComponent>(TEXT("BehaviorComponent"));
}

void ASOCAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ASOCAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASOCAIController::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}
#pragma endregion
